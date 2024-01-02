#include <SPI.h>
#include <Ethernet.h>
#include <HttpClient.h>

//Nesta versão do código eu estava fazendo uma requisicao para uma API para que entao a informação fosse gravada no banco. Porém encontrei problemas,
//pois o Shield Ethernet w5100 do arduino só consegue fazer requicisões em http, e o servidor era https. Então isso me impossibilitou de usar APIs.

char endpoint[] = "/insert";
int pinoSensorTensao = A0;

byte mac[] = { 0xA4, 0x28, 0x72, 0xCA, 0x55, 0x2F };
IPAddress ip(192, 168, 1, 110);
IPAddress server(216,24,57,253);
EthernetClient client;

bool estadoAntigo = false;
bool estadoAtual = false;

void setup() {
  pinMode(pinoSensorTensao, INPUT);
  // Adicione mensagens de depuração
  Serial.println("Configurando Ethernet...");
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
  delay(1000);
  Serial.println("Configuração concluída.");
  Serial.println("Feito por H. Fontenele");
}

void loop() {
  delay(2500);
  estadoAntigo = estadoAtual;
  int valorSensor = analogRead(pinoSensorTensao);
  String json;
  Serial.println("Valor do sensor: " + String(valorSensor));

  if (valorSensor < 100) {
    Serial.println("Desligado");
    estadoAtual = false;
    json = "{\"status\":false,\"name_room\":\"1\"}";
  } else {
    Serial.println("Ligado");
    estadoAtual = true;
    json = "{\"status\":true,\"name_room\":\"1\"}";
  }

  if (estadoAntigo != estadoAtual) {
    // Faz a requisição POST
    Serial.println("Tentando se conectar ao servidor...");
    if (client.connect(server, 80)) {
      Serial.println("Conectado ao servidor com sucesso!");
      client.println("POST " + String(endpoint) + " HTTP/1.1");
      client.println("Host: " + String("https://arduinoapi-u5cp.onrender.com"));
      client.println("Content-Type: application/json");
      client.println("Connection: close");
      client.print("Content-Length: ");
      client.println(json.length());
      client.println();
      client.print(json);

      Serial.println("Mudança de estado detectada!");
      Serial.println("Enviando requisição POST para o servidor...");
      delay(1000);
      // Aguarda a resposta do servidor
      while (client.connected()) {
        if (client.available()) {
          char c = client.read();
          Serial.print(c);
        }
      }

      // Fecha a conexão
      client.stop();
    } else {
      Serial.println("Falha ao conectar ao servidor");
    }
  }else{

  }
}