# Auditoria inicial do QElectroTech

Data da consulta: 26-11-2026

## Fontes consultadas

- Repositório: https://github.com/qelectrotech/qelectrotech-source-mirror
- README consultado (blob): 47e5432b3610115dc1dcb159e3feea82a8f3a904
- CMakeLists.txt consultado (blob): d4d7274c5da6f1d7c3051f04f3f7ca58e62aba3b
- LICENSE consultado (blob): 9414b49f3743265347c8371d09de81e4d38675ad

## Constatações confirmadas

1. O README descreve o QElectroTech como aplicação livre e open source para desenho de diagramas e esquemas, principalmente documentação elétrica.
2. O README declara que não existem funcionalidades integradas de simulação ou cálculo elétrico, e que esse não é o objetivo do projeto original.
3. O README declara licenciamento GNU GPL e aponta para GPL-2.0.
4. A receita de compilação indicada pelo README começa por clonar o repositório com submódulos: `git clone --recursive https://github.com/qelectrotech/qelectrotech-source-mirror.git`.
5. O README consultado indica Qt 6.x, C++, CMake, KF6 (incluindo KCoreAddons e KWidgetsAddons) e XML para projetos, elementos e legendas.
6. O CMakeLists.txt consultado declara a versão 0.200.1, exige C++17 e procura Qt6. Também verifica Qt6::GuiPrivate; QtPdf e Qml são componentes opcionais conforme a configuração encontrada.
7. O ficheiro LICENSE consultado contém o texto da GNU General Public License versão 2.

## Consequências para o ElectroCAD

- QElectroTech é uma base plausível para o editor de esquemas, interface gráfica, documentos e elementos.
- O modelo de cálculo elétrico, verificações de engenharia, gestão avançada de equipamentos, layout físico e serviços multiutilizador terão de ser desenvolvidos separadamente ou integrados a partir de componentes avaliados.
- A compatibilidade com os formatos XML existentes deve ser preservada e coberta por testes.
- A biblioteca de elementos não deve ser assumida como tendo a mesma licença do código sem auditar os ficheiros e avisos próprios da coleção.
- Símbolos oficiais IEC 60617 exigem confirmação de direitos/licença e proveniência; a coleção comunitária do QElectroTech não será automaticamente rotulada como biblioteca IEC oficial validada.

## Decisão provisória de versão

O CMakeLists.txt consultado pertence à linha 0.200.1 e usa Qt 6/C++17. O README diferencia uma versão estável 0.100 de uma linha de desenvolvimento 0.200.x e alerta que a versão de desenvolvimento pode conter funcionalidades incompletas.

Não fixar ainda uma versão de produção. Antes disso é necessário comparar a tag estável com a linha Qt 6, verificar a documentação de compilação Windows e reproduzir um build limpo. O SHA dos blobs consultados não é, por si só, uma identificação do commit completo do repositório.

## Estado desta auditoria

Auditoria documental inicial concluída. Ainda não foi clonado nem integrado o código-fonte, não foi criado um build e não foi testado um executável. Próximo passo técnico: obter a árvore completa e submódulos do upstream, fixar um commit/tag, inspecionar CMake, dependências e licenças de elementos, e reproduzir compilação num runner Windows.
