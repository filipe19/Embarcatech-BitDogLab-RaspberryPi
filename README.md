
# Sistema de Iluminação Adaptativa com LEDs RGB para Aplicação em Estudos do Comportamento de Crianças com TDAH
----------------------------------------------------------------------------------------------------------------
==========
Instituto_Hardware_BR - Softex - Embarcatech - 2025

### Introduction
------------

Estudos comprovam que a iluminação adequada tem um impacto significativo no comportamento e desempenho de alunos com TDAH [1][4]. Crianças com esse transtorno são altamente sensíveis a estímulos externos, e a exposição a ambientes com iluminação inadequada pode aumentar os sintomas de desatenção, hiperatividade e impulsividade. Por outro lado, ajustes adequados na iluminação podem favorecer a concentração, reduzir a agitação e promover um ambiente mais propício para a aprendizagem.
A criação de um sistema acessível e programável de iluminação adaptativa justifica-se como uma ferramenta auxiliar na educação inclusiva, permitindo que educadores personalizem o ambiente escolar conforme as necessidades individuais dos alunos. Tecnologias emergentes, como sensores e sistemas automatizados, demonstram um potencial significativo para auxiliar na autorregulação emocional e comportamental dessas crianças [2].
A escolha da BitDogLab com a Raspberry Pi Pico W como plataforma de desenvolvimento permite a implementação de uma solução de baixo custo, eficiente e personalizável, viabilizando sua aplicação em diferentes contextos educacionais [6][7]. Além disso, o sistema possibilita ajustes manuais e perfis pré-definidos de iluminação, tornando sua utilização prática e intuitiva para professores e gestores escolares. Dessa forma, o projeto contribui diretamente para o desenvolvimento de estratégias pedagógicas mais inclusivas, alinhadas às necessidades dos alunos com TDAH e demais transtornos do neurodesenvolvimento.

### Objetivo Geral

Desenvolver um sistema de iluminação adaptável para salas de aula, permitindo ajustes personalizados de luz para criar um ambiente mais adequado à regulação emocional, concentração e redução da agitação em alunos com Transtorno de Déficit de Atenção e Hiperatividade (TDAH). O sistema será baseado no módulo BitDogLab com Raspberry Pi Pico W, permitindo o controle automatizado da iluminação por meio de LEDs RGB, ajustando-se dinamicamente às necessidades dos alunos.

div align="center"

<img width="100%" align="left" src="figuras\0bitdoglab.png">

/div

#### diagrama de blocos 

### Requisitos de Hardware e Software
O sistema é composto por componentes físicos e programas necessários para seu funcionamento:
Hardware:
Raspberry Pi Pico W
LEDs RGB
Pushbuttons
Display OLED
Software:
Firmware desenvolvido em linguagem C para controle do sistema.
Interfaces de configuração para ajuste da iluminação.


<img width="100%" align="left" src="figuras\2bitdoglab.png">
#### Placa BitDogLab durante os testes com o Led-RGB, Display e botões


### Referências

[1] AMERICAN PSYCHIATRIC ASSOCIATION. DSM-5: Manual Diagnóstico e Estatístico de Transtornos Mentais. 5. ed. Arlington: APA, 2013.

[2] SHELTON, S. H. Teacher Perspectives on Classroom Lighting Conditions for Students with and without an ADHD Diagnosis. 2020. Dissertação (Mestrado em Design de Interiores) – Sidney O. Smith Graduate School, Brenau University, Gainesville, 2020.

[3] CIBRIAN, F. L.; LAKES, K. D.; SCHUCK, S. E. B.; HAYES, G. R. The potential for emerging technologies to support self-regulation in children with ADHD: A literature review. International Journal of Child-Computer Interaction, [s. l.], v. 31, p. 100421, mar. 2022. Elsevier.

[4] SIMPSON, J. F. The Calming Effects of Modified Lighting. 2016. Tese (Doutorado em Educação) – University of Mississippi, Oxford, 2016.

[5] LOVISA, M. Multi-sensory environments adaptation for the relaxation of children with neurodevelopmental disorders. 2017. Dissertação (Mestrado em Engenharia Industrial e da Informação) – Politecnico di Milano, Milão, 2017.

[6] DAVIDSON, Z. C. M.; DANG, S.; VASILAKOS, X. Blended Laboratory Design Using Raspberry Pi Pico for Digital Circuits and Systems. IEEE Transactions on Learning Technologies, [s. l.], p. 1-10, 2024.

[7] FRUETT, F.; BARBOSA, F. P. S.; FRAGA, S. C. Z.; GUIMARÃES, P. I. A. Empowering STEAM Activities With Artificial Intelligence and Open Hardware: The BitDogLab. IEEE Transactions on Education, [s. l.], v. 67, n. 3, p. 1-9, 2024. DOI: 10.1109/te.2024.3377555. ISSN: 1557-9638.

[8] VEITCH, J. A. Psychological Processes Influencing Lighting Quality. Journal of the Illuminating Engineering Society, [s. l.], v. 30, n. 1, p. 124-140, 2001. National Research Council of Canada, Ottawa.

[9] ÖZTÜRK, M. A Predictive Control System for Indoor Lighting. 2017. Trabalho de Conclusão de Curso (Graduação em Engenharia) – Institute of Architecture of Application Systems, University of Stuttgart, Stuttgart, 2017.

[10] YOUNG, H. D.; FREEDMAN, R. A. Física IV: Ótica e Física Moderna. Pearson Education do Brasil Ltda, 2016.

[11] GREEN, K. Sensibilidade à luz no TDAH: a relação com a hipersensibilidade e o processamento sensorial. 2018. Disponível em: <https://www.theraspecs.com/blog/adhd-light-sensitivity-hypersensitivity-sensory-processing>. Acesso em 15 de fevereiro de 2025.

[12] TIMOTEO. Bitdoglab-C. Pico SDK applications for the BitDogLab, written in C. Disponível em: < https://github.com/BitDogLab/BitDogLab-C>. Acesso em 15 de fevereiro de 2025.

[13] SHABAZ. PicoChroma - LED Lighting. Disponível em: <https://github.com/shabaz123/picochroma>. Acesso em 15 de fevereiro de 2025.


### Apêndice
[] Link do vídeo apresentação deste projeto, disponível em: < https://youtube.com/shorts/BVoW-QmkCpc >  

### Arquivos 

CMakeLists.txt --> 

pico_sdk_import.cmake --> 

rgb_pwm.c --> 

<img width="100%" align="left" src="figuras\1bitdoglab.png">
#### Ambiente de desenvolvimento Visual Studio Code durante a implementação do projeto
