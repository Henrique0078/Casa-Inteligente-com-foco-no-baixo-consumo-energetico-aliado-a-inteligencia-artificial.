# Casa Inteligente com foco no baixo consumo energético aliado a inteligência artificial.
 Repositório para Fins Acadêmicos - Casa Inteligente com foco no baixo consumo energético aliado a inteligência artificial.

Os códigos disponíveis neste repositório têm como objetivo principal a implementação de um sistema para registrar informações sobre o status da luz ambiente. Desenvolvido para fins acadêmicos, o sistema grava dados como data, dia da semana e mês, proporcionando uma abordagem prática para a análise de padrões de uso.

## Desafios Enfrentados
Durante o processo de construção, enfrentei desafios notáveis que influenciaram as escolhas de implementação:

**Limitações do Shield Ethernet w5100:**
O Shield Ethernet w5100 utilizado mostrou-se incapaz de realizar requisições HTTPS. Isso limitou a possibilidade de utilizar APIs em nuvem para armazenamento de dados.

**Problemas de Conexão com a Rede:**
Observou-se que, ao fornecer todas as informações necessárias para o Shield Ethernet se conectar à rede, a conexão não era estabelecida. A solução foi alcançada ao passar apenas o endereço MAC e IP configurados para o Arduino.

## Alternativa Adotada
Diante dos desafios apresentados, a solução adotada no código final (ArduinoV3) consistiu em uma abordagem direta, conectando-se diretamente a um banco de dados MySQL para realizar a gravação das informações. Essa escolha permitiu superar as limitações do Shield Ethernet w5100 e alcançar os objetivos propostos.

## Banco de dados
O repositório inclui o código SQL utilizado para criar o banco de dados necessário para armazenar as informações do sistema. Este script SQL está disponível para referência e utilização.
