#include <PubSubClient.h>

#include <UIPEthernet.h>

#include <SPI.h>


//Define o endereço MAC que será utilizado
byte mac[] = {0x68,0x08,0x2F,0xA1,0x77,0x25};


int pino2 = 2;
bool estado_sensor;
boolean mensagem;

//Inicia o cliente Ethernet
EthernetClient client;

PubSubClient mqttClient(client);

void setup() {
    //Inicia o controlador Ethernet e solicita um IP para o servidor de DHCP
    Ethernet.begin(mac);

    //Inicia o monitor Serial
    Serial.begin(9600);
    pinMode(pino2, INPUT_PULLUP);

    mqttClient.setServer("54.173.148.114",1883);

    //Exibe no Monitor Serial as informações sobre o IP do Arduino
    Serial.print("O IP do Arduino e: ");
    Serial.println(Ethernet.localIP());

    //Exibe no Monitor Serial as informações sobre a Máscara de Rede do Arduino
    Serial.print("A Mascara de Rede do Arduino e: ");
    Serial.println(Ethernet.subnetMask());

    //Exibe no Monitor Serial as informações sobre o Gateway do Arduino
    Serial.print("O Gateway do Arduino e: ");
    Serial.println(Ethernet.gatewayIP());

    //Exibe uma linha em branco
    Serial.println("");

}

void loop() {

      mqttClient.connect("marianagennari");
      estado_sensor = digitalRead(pino2);

    if (estado_sensor == 0)

    {

      Serial.println("o rack esta fechado");
      mensagem = mqttClient.publish("marianagennari", "Fechado");
      
    }

    else

    {

      Serial.println("o rack esta aberto");
      mensagem = mqttClient.publish("marianagennari", "Aberto");
      
    }

  mqttClient.loop();
  Serial.println(mensagem);

   
}
