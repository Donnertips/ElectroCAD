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


## Segunda ronda — submódulos, dependências e coleção de elementos

Data da consulta: 26-11-2026

### Submódulos declarados

O ficheiro `.gitmodules` do upstream (blob `82164f390f469e581af81ac95c759958323ea5bb`) declara quatro submódulos:

| Caminho | Repositório | Função/observação |
|---|---|---|
| `pugixml` | https://github.com/zeux/pugixml | Biblioteca XML |
| `SingleApplication` | https://github.com/itay-grudev/SingleApplication | Gestão de instância única Qt |
| `elements` | https://github.com/qelectrotech/qelectrotech-elements | Coleção oficial de elementos do QElectroTech |
| `doxygen-awesome-css` | https://github.com/jothepro/doxygen-awesome-css | Estilos da documentação Doxygen |

A coleção `qelectrotech-elements` tem um ficheiro próprio `ELEMENTS.LICENSE`. Este permite usar, editar e integrar os elementos em esquemas elétricos sem condição, independentemente da licença final dos esquemas. A redistribuição da coleção, ou de parte dela, fora de um esquema elétrico está sujeita a CC BY 3.0 e atribuição. O ficheiro também proíbe utilizar os elementos como dados de amostra para construir modelos de aprendizagem automática. A licença e o âmbito devem ser respeitados na distribuição do ElectroCAD.

### Dependências descobertas no CMake

- O CMake procura Qt 6 e exige o alvo `Qt6::GuiPrivate` para a funcionalidade de hiperligações PDF.
- SQLite3 é dependência obrigatória; a extensão session é detetada e, se ausente, o histórico de alterações guardadas fica limitado.
- KF6 CoreAddons e WidgetsAddons são usados; o projeto pode obtê-los via FetchContent ou encontrá-los no sistema, conforme opções de build.
- O CMake fixa commits específicos para pugixml v1.15 e SingleApplication v3.2.0 e commits correspondentes a KF v6.10.0. Esta fixação por SHA é uma boa prática de reprodutibilidade e deve ser preservada.
- QtPdf e QtQml são opcionais na configuração consultada; a ausência desativa funcionalidades associadas.
- O CMake ativa testes por omissão através de `PACKAGE_TESTS`.

### Inconsistência de versão a resolver

O README consultado afirma que a versão estável é 0.100 (lançada em 25-01-2026) e descreve a linha de desenvolvimento como 0.100.1 ou 0.200.0, enquanto o `CMakeLists.txt` consultado declara `project(... VERSION 0.200.1)`. Não escolher uma destas versões apenas com base no README ou no número do CMake: a seleção exige identificar tags e commits completos, comparar o estado do código e executar builds de referência.

### Funcionalidades já existentes que reduzem trabalho duplicado

O README upstream documenta, entre outras: editor de elementos, ligações de condutores, referências cruzadas automáticas, numeração, tabelas de conteúdos, nomenclaturas/listas, exportação CSV, impressão PDF multipágina e exportação SVG/imagem. Estas capacidades devem ser verificadas por testes no commit escolhido antes de serem reimplementadas no ElectroCAD.

### Decisão técnica atualizada

Manter QElectroTech como candidato a motor do editor e preservar os seus formatos. Não iniciar ainda a cópia/inclusão da coleção de elementos nem fixar uma versão de produção. Próximos bloqueios objetivos: obter commit/tag completo e estado dos submódulos, apurar licenças de cada componente e da coleção, e validar build limpo Windows x64 com as dependências exatas.

### Limites da verificação

Esta ronda foi uma inspeção documental dos ficheiros acessíveis pela API do GitHub. Não equivale a clone recursivo, inspeção de todos os ficheiros/submódulos, análise de licença elemento a elemento ou compilação. Nenhum build ou executável foi produzido nesta etapa.


## Terceira ronda — baseline fixado e evidência CI

A árvore Git do commit upstream `b49ce16c42b99e458e38935f39b919d56582e54e` foi consultada diretamente. Os gitlinks dos quatro submódulos estão registados em `UPSTREAM_BASELINE.md`, juntamente com os SHAs exatos e as licenças identificadas.

O commit `b49ce16c42b99e458e38935f39b919d56582e54e` é agora a referência técnica para a primeira reprodução e integração experimental, não uma decisão definitiva de versão de produção. O commit tem versão CMake 0.200.1 e corresponde à linha de desenvolvimento/nightly.

Foi confirmada a execução bem-sucedida da pipeline oficial Windows Build para este SHA (run 45806034743), incluindo checkout recursivo, CMake, Ninja, testes unitários, verificação do executável e empacotamento. A pipeline Windows MSI (run 45810890238) também terminou com sucesso. A execução Linux build e testes (run 45791966123) terminou com sucesso. O release upstream publicou instalador Windows x64 para o mesmo commit. Esta evidência pertence ao CI upstream e não equivale a uma compilação do ElectroCAD.

O guia INSTALL.md documenta MSVC e MinGW, mas a pipeline Windows de referência usa MSYS2 UCRT64/MinGW-w64. A primeira reprodução deve utilizar o mesmo toolchain para reduzir diferenças.

### Licenças de submódulos identificadas

- pugixml: MIT.
- SingleApplication: licença permissiva com cláusula expressa de atribuição/inclusão da licença; exemplos com nota própria.
- doxygen-awesome-css: MIT.
- Coleção de elementos: licença própria ELEMENTS.LICENSE, com permissão para integração em esquemas elétricos e CC BY 3.0 para redistribuição fora de esquemas.
- KF6: licenças dos commits efetivamente distribuídos e dependências transitivas ainda carecem de inventário.

Ver `docs/UPSTREAM_BASELINE.md` e `THIRD_PARTY_NOTICES.md` para detalhes e SHAs.

### Estado atualizado

A auditoria documental dos submódulos e do baseline está substancialmente avançada. Não foi feito clone recursivo local, não foi executada compilação no repositório ElectroCAD e não foi gerado executável ElectroCAD. A seleção de produção e a reprodução independente do build continuam abertas.
