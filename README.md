# HealthGuardEnviroMonitor-GSEdge
IoT solution to collect data monitoring patients room salubrity

## O problema de saúde: Ambientes Insalubres
No mundo moderno, onde passamos a maior parte do nosso tempo em ambientes fechados, a qualidade do ar que respiramos, a temperatura e a iluminação dos espaços em que vivemos e trabalhamos têm um impacto direto em nossa saúde. Muitas vezes, desconhecemos os riscos associados a ambientes insalubres, o que pode levar a uma série de problemas de saúde, especialmente para pacientes que já enfrentam desafios médicos. A exposição prolongada a temperaturas inadequadas, níveis inadequados de umidade e iluminação inadequada pode agravar condições de saúde preexistentes ou até mesmo desencadear novos problemas médicos. É crucial reconhecer a importância de ambientes saudáveis na promoção do bem-estar e na recuperação eficaz de pacientes. Nesse sentido, desenvolvemos uma solução chamada HealthGaurd EnviroMonitor.

## HealthGuard EnviroMonitor
Essa solução consiste em um dispositivo instalado capaz de realizar medições no ambiente com sensores embutidos, tais como: temperatura, umidade e luminosidade. A ideia é coletar e fornecer esses dados para um profissional da saúde em tempo real, a fim de monitor a salubridade do ambiente em que seu paciente está inserido e alertado a respeito dos cuidados e prevenções a serem tomadas. Além disso, a solução IoT empregada também enviará alertas no celular do paciente com mensagens de prevenções a serem tomadas dependendo das condições do ambiente (caso estiver muito calor e seco, se hidratar melhor. Caso estiver com a temperatura alta, muito úmido e escuro, tomar cuidado com a proliferação de fungos e bactérias. E assim por diante...). O dispositivo também possúi LED's visuais (vermelho, amarelo e verde) capaz de ilustrar as condições do ambiente de maneira visual (vermelho: "ambiente insalubre", amarelo:"ambiente não muito salubre" e verde:"ambiente salubre").
<div align="center">
  <img src="https://github.com/gui2604/HealthGuardEnviroMonitor-GSEdge/assets/128194162/be968a3a-ba93-4c6c-a674-1b3ed451bb31" width="700px">
</div>
### Componentes Utilizados no Circuito:
  - ESP32
  - DHT22(sensor de umidade e temperatura)
  - LDR (sensor de luz)
  - LED's (vermelho, amarelo e verde)
  - 3 resistores 220 Ohms
  - 1 resistor 10 kOhms
  - 1 Protoboard
  - 5 cabos macho-macho
  - 8 cabos macho-femea
  - 1 cabo femea-femeea
  - 1 cabo micro-USB
  
