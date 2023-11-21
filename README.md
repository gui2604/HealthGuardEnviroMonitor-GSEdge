# HealthGuardEnviroMonitor-GSEdge
IoT solution to collect data monitoring patients room salubrity

## O problema de saúde: Ambientes Insalubres
No mundo moderno, onde passamos a maior parte do nosso tempo em ambientes fechados, a qualidade do ar que respiramos, a temperatura e a iluminação dos espaços em que vivemos e trabalhamos têm um impacto direto em nossa saúde. Muitas vezes, desconhecemos os riscos associados a ambientes insalubres, o que pode levar a uma série de problemas de saúde, especialmente para pacientes que já enfrentam desafios médicos. A exposição prolongada a temperaturas inadequadas, níveis inadequados de umidade e iluminação inadequada pode agravar condições de saúde preexistentes ou até mesmo desencadear novos problemas médicos. É crucial reconhecer a importância de ambientes saudáveis na promoção do bem-estar e na recuperação eficaz de pacientes. Nesse sentido, desenvolvemos uma solução chamada HealthGaurd EnviroMonitor.

## HealthGuard EnviroMonitor
Essa solução consiste em um dispositivo instalado capaz de realizar medições no ambiente com sensores embutidos, tais como: temperatura, umidade e luminosidade. A ideia é coletar e fornecer esses dados para um profissional da saúde em tempo real, a fim de monitor a salubridade do ambiente em que seu paciente está inserido e alertado a respeito dos cuidados e prevenções a serem tomadas. Além disso, a solução IoT empregada também enviará alertas no celular do paciente com mensagens de prevenções a serem tomadas dependendo das condições do ambiente (caso estiver muito calor e seco, se hidratar melhor. Caso estiver com a temperatura alta, muito úmido e escuro, tomar cuidado com a proliferação de fungos e bactérias. E assim por diante...). O dispositivo também possúi LED's visuais (vermelho, amarelo e verde) capaz de ilustrar as condições do ambiente de maneira visual (vermelho: "ambiente insalubre", amarelo:"ambiente não muito salubre" e verde:"ambiente salubre").
<div align="center">
  <img src="https://github.com/gui2604/HealthGuardEnviroMonitor-GSEdge/assets/128194162/be968a3a-ba93-4c6c-a674-1b3ed451bb31" width=700px>
</div>
<h2>Componentes Utilizados no Circuito:</h2>
<li>
  <ul>- ESP32</ul>
  <ul>- DHT22(sensor de umidade e temperatura)</ul>
  <ul>- LDR (sensor de luz)</ul>
  <ul>- LED's (vermelho, amarelo e verde)</ul>
  <ul>- 3 resistores 220 Ohms</ul>
  <ul>- 1 resistor 10 kOhms</ul>
  <ul>- 1 Protoboard</ul>
  <ul>- 5 cabos macho-macho</ul>
  <ul>- 8 cabos macho-femea</ul>
  <ul>- 1 cabo femea-femeea</ul>
  <ul>- 1 cabo micro-USB</ul>
</li>
<h2>Tela do Circuito:</h2>
<div align="center">
  <img src="https://github.com/gui2604/HealthGuardEnviroMonitor-GSEdge/assets/128194162/a0c4fed0-9a8e-486f-b9e0-67f846552910" width=700px>
</div>
Os dados são coletados por esse circuito, e o ESP32 conectado à internet pode enviá-los para sistemas de monitoramento. Desde o software do profissional de saúde que possúi clientes cadastrados a fim de acompanhar a salubridade dos ambientes em que eles estão inseridos podendo realizar orientações médicas a fim de prevenir doenças, até mensagens de alerta para o celular do paciente, para que ele receba avisos em tempo real dependendo das condições do ambiente. 
<div display="flex" align="center">
  <img src="https://github.com/gui2604/HealthGuardEnviroMonitor-GSEdge/assets/128194162/6319ec16-9977-4c46-a0b6-a8a4abab67ea" width=700px>
  <img src="https://github.com/gui2604/HealthGuardEnviroMonitor-GSEdge/assets/128194162/cbb71ce3-b21d-4cb0-9877-ed78ac3177e3" width=700px>
</div>
O fluxo IoT dessa aplicação funciona da seguinte forma: O circuito do dispositivo da HealthGuard EnviroMonitor coleta as informações e envia pelo ESP32 via protocolo MQTT para algum broker, disponibilizando as informações. O servidor local do sistema recebe os dados via tópico MQTT e converte-os para dashboards visuais para o profissional de saúde e também faz o envio do alerta vioa WhatsApp para o paciente. Como demonstrado no fluxo a seguir:
<div align="center">
  <img src="" width=700px>
</div>

