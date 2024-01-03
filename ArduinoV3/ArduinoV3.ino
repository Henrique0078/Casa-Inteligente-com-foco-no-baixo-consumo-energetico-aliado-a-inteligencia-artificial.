#include <SPI.h>
#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

//Nesta versão, como alternativa ao problema de não poder usar APIs, eu optei por fazer uma conexao diretamente com o banco de dados, que só foi possivel
//por conta desta biblioteca de MySQL que ja tem está funcionalidade nativa.

char endpoint[] = "/insert";
int pinoSensorTensao = A0;

byte mac[] = { 0xA4, 0x28, 0x72, 0xCA, 0x55, 0x2F };
IPAddress ip(192, 168, 1, 110);
IPAddress server_addr(91, 208, 207, 108);
char user[] = "usuario";
char password[] = "senha";

char INSERT_DATA[145]; 
char insert_error[145];

bool estadoAntigo = false;
bool estadoAtual = false;
bool error = false;

EthernetClient client;
MySQL_Connection conn(&client);
MySQL_Cursor* cursor;

void setup() {
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
  Serial.println("Feito por H. Fontenele");
  Serial.println("\n");
  delay(1000);
}

void loop() {
  while(!conn.connected()){
    conn.connect(server_addr, 3306, user, password);
    delay(1500);
  }

  delay(2500);
  estadoAntigo = estadoAtual;
  int valorSensor = analogRead(pinoSensorTensao);
  String json;
  Serial.println("Valor do sensor: " + String(valorSensor));

  if (valorSensor < 300) {
    Serial.println("Desligado");
    estadoAtual = false;
  } else {         
    Serial.println("Ligado");
    estadoAtual = true;
  }

  snprintf(INSERT_DATA, sizeof(INSERT_DATA), "INSERT INTO bto9gojdlcbmuy1jwowf.dataset (name_room_ds, status_ds, weekday_ds, month_ds) VALUES ('1', %d, DAYNAME(NOW()), MONTHNAME(NOW()))", estadoAtual ? 1 : 0);
  
  if(error){
    delay(500);
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    if(cur_mem->execute(insert_error)){
      Serial.println("Data recorded.");
      error = false;
    }else{
      error = true;
    }
    delete cur_mem;
  }

  if (estadoAntigo != estadoAtual) {
    delay(1000);
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    if(cur_mem->execute(INSERT_DATA)){
      Serial.println("Data recorded.");
    }else{
      error = true;
      strcpy(insert_error, INSERT_DATA);
    }
    delete cur_mem;
  }
  
  delay(2500);
}
