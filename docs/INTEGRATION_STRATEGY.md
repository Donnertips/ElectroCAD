# Estratégia de integração do motor QElectroTech

## Decisão técnica

O ElectroCAD é desenvolvido como uma única aplicação Windows baseada no QElectroTech. O código upstream fica identificável e fixado num commit; os módulos próprios são acrescentados ao mesmo executável. Não será criado um segundo editor nem um wrapper que lance outra aplicação.

O workflow CI faz checkout do upstream no SHA registado em `UPSTREAM_BASELINE.md`, configura a árvore CMake hierárquica e compila o alvo de aplicação integrado. A adoção do upstream como submódulo Git em `external/qelectrotech` continua pendente; o checkout atual é feito pelo workflow.

## Baseline e build

Baseline auditado: QElectroTech 0.200.1-dev, commit `b49ce16c42b99e458e38935f39b919d56582e54e`, Qt6/KF6. É uma linha experimental e não é declarada versão de produção.

A configuração CMake hierárquica, compilação Windows x64, testes e verificação do executável passaram nos runs:
- PR #1: run 45869976768.
- PR #2: run 45881881930.
- PR #3: runs 45901278849 e 45901297058.

O executável produzido pelo CI é um artefacto de integração, não um instalador de produção. Deployment completo de Qt, recursos, traduções, elementos, modelos e instalação portátil ainda não foi validado.

## Módulos ElectroCAD implementados

`src/electrocad/electricalmodel.*` implementa um modelo C++17 de terminais, ligações e redes explícitas, com validação de IDs e prevenção de ligações inválidas/duplicadas.

`QetDiagramAdapter` lê `Diagram::elements()`, `Diagram::conductors()`, `Element::terminals()`, UUIDs de elementos/terminais e endpoints válidos de condutores. Cria um snapshot read-only, agrupando endpoints conectados em redes por componentes conexos. Não infere continuidade interna de aparelhos, não altera o diagrama e não substitui algoritmos de potencial do QElectroTech.

## Estado integrado

- PR #1: fundação CMake e núcleo inicial integrados.
- PR #2: redes e derivações integradas.
- PR #3: adaptador nativo de topologia integrado na `main` pelo commit `1ab608286c601b1a9e8c15f13c01ff1f540647c7`; CI Windows x64 passou build, testes e verificação do executável.
- Artefacto CI: `electrocad-qelectrotech-integration-win64`; não é um instalador de produção.

## Próxima etapa técnica

Ligar o snapshot topológico ao ciclo de vida do editor: analisar os comandos de criação/edição/remoção de condutores, movimentos de terminais, gestão de seleção e undo/redo. Definir uma sincronização consistente sem mutações laterais no modelo. Depois acrescentar persistência de IDs ElectroCAD e testes funcionais de abrir/guardar/exportar projetos de referência.

## Regras de manutenção

- Não editar silenciosamente o upstream: patches explícitos ou commits num fork com histórico.
- Registar SHA upstream, submódulos e toolchain.
- Atualizações upstream só entram após build, testes e revisão.
- Preservar formatos de projeto; migrações exigem testes de ida e volta.
- Não declarar funcionalidades elétricas, símbolos IEC ou conformidade normativa como validados sem evidência independente.
- Fechar instalador e inventário de licenças apenas depois de conhecer as DLLs e recursos realmente distribuídos.

## Critério de fecho da Fase 1

A fase permanece aberta até integração com o editor, sincronização/undo, persistência, deployment e testes funcionais reproduzíveis com projetos reais.
