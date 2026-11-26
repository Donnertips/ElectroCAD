# Estratégia de integração do motor QElectroTech

## Decisão técnica

A integração será feita como **uma única aplicação Windows**, mantendo o código upstream do QElectroTech identificável e fixado num commit, e acrescentando os módulos ElectroCAD ao mesmo executável.

A primeira abordagem a validar é:

1. Manter o QElectroTech como submódulo Git em `external/qelectrotech`, fixado no commit registado em `UPSTREAM_BASELINE.md`.
2. Fazer do repositório ElectroCAD o projeto CMake de topo.
3. Adicionar o diretório upstream com `add_subdirectory(external/qelectrotech)`.
4. Compilar os módulos ElectroCAD como biblioteca(s) própria(s), ligada(s) ao alvo de objetos upstream `qelectrotech_objects` e ao executável QElectroTech.
5. Introduzir os pontos de integração da interface através de alterações pequenas, documentadas e isoladas (patches/ficheiros de integração), sem manter uma cópia opaca de todo o código upstream.
6. Alterar gradualmente identidade visual, menus, fluxos e funcionalidades para ElectroCAD, preservando a atribuição, avisos e licenças do QElectroTech.

O utilizador final deverá iniciar uma única aplicação ElectroCAD. Não haverá um segundo editor QElectroTech separado nem uma aplicação-wrapper que apenas lance outro executável.

## Evidência e limites da auditoria CMake

No commit upstream `b49ce16c42b99e458e38935f39b919d56582e54e`, o CMake de topo:

- declara o projeto `qelectrotech` e a versão 0.200.1;
- cria o alvo de biblioteca de objetos `qelectrotech_objects`;
- cria o executável `qelectrotech`;
- configura Qt 6, SQLite, KDE Frameworks, submódulos e dependências;
- acrescenta testes e regras de instalação no mesmo diretório.

Isto oferece pontos de ligação concretos para acrescentar código ao executável existente. Contudo, a presença de `project()` no CMake upstream, variáveis de diretório, opções globais, regras de instalação e pressupostos sobre `CMAKE_SOURCE_DIR`/alvos ainda têm de ser testados num build CMake hierárquico. **A integração por `add_subdirectory` é uma hipótese técnica promissora, não uma compatibilidade já demonstrada.**

## Critérios para aceitar a abordagem

Antes de migrar código ou desenvolver funcionalidades sobre esta estrutura, um teste de integração deverá provar:

- configuração CMake a partir da raiz ElectroCAD;
- checkout recursivo do submódulo no SHA exato;
- build do executável único em Windows x64;
- execução de todos os testes upstream;
- inclusão de um módulo ElectroCAD mínimo no mesmo executável;
- instalação/deployment de Qt e dependências sem perder recursos, traduções, elementos e modelos;
- funcionamento de abrir, guardar e exportar projetos de referência;
- ausência de alterações não intencionais aos ficheiros upstream.

Se o CMake hierárquico falhar por pressupostos estruturais, a alternativa é manter um fork de integração do QElectroTech como árvore de compilação principal, com o upstream como remoto e commits de sincronização explícitos. Não se deve contornar uma incompatibilidade com um segundo executável ou com cópias manuais de fontes.

## Organização prevista

- `external/qelectrotech/`: submódulo upstream fixado por SHA.
- `src/electrocad/`: módulos e lógica próprios.
- `src/integration/`: adaptadores e pontos de ligação à aplicação, quando necessários.
- `tests/electrocad/`: testes unitários e de integração dos módulos próprios.
- `patches/upstream/`: apenas se forem necessários patches pequenos e reproduzíveis; cada patch deve explicar motivo, ficheiros afetados e forma de reaplicação.

A estrutura final pode ser ajustada pelo teste de integração, sem mudar o princípio de aplicação única.

## Regras de manutenção

- Não editar silenciosamente o submódulo: alterações upstream devem ser patches explícitos ou commits num fork com histórico.
- Registar sempre SHA upstream, SHAs dos submódulos e toolchain usada.
- Atualizações upstream só entram após build, testes e revisão dos conflitos.
- Preservar os formatos de projeto; qualquer migração exige testes de ida e volta e cópias de referência.
- Não declarar funcionalidades elétricas, símbolos IEC ou conformidade normativa como validados sem evidência técnica independente.
- O instalador e o inventário de licenças só são fechados depois de conhecer as DLLs e os recursos realmente distribuídos.

## Primeiro módulo ElectroCAD

Foi criado `src/electrocad/electricalmodel.*`, um núcleo C++17 inicial que regista terminais identificados por componente/terminal e liga pares de terminais existentes. Rejeita identificadores vazios, terminais desconhecidos, auto-ligações e ligações duplicadas (mesmo quando a ordem dos extremos é invertida). Os testes próprios ficam em `src/electrocad/tests/` e são registados no CTest. O objeto é adicionado ao alvo `qelectrotech`, pelo que a intenção é compilar o código próprio dentro do executável único, sem produzir uma segunda aplicação.

Este núcleo ainda não representa redes, nós com múltiplas derivações, continuidade interna de aparelhos, potenciais ou referências cruzadas. Não se deve inferir qualquer uma dessas funções a partir de uma simples ligação.

## Estado

A estratégia de integração e o primeiro módulo próprio foram integrados em `main` através do PR #1 (merge commit `19c51ccc8112ebc0d31fca53dba2ec8949d9abf2`). O workflow Windows associado ao PR #1 foi criado, mas permanece em fila; ainda não há confirmação de configuração CMake, compilação ou testes integrados.

O núcleo atual apenas regista terminais e liga pares de terminais. A compatibilidade CMake hierárquica, o deployment, os recursos/traduções/elementos, e os fluxos de abrir, guardar e exportar continuam por validar. A Fase 1 permanece aberta. O próximo marco é obter um build Windows verde no commit integrado e corrigir incompatibilidades com base nos logs reais, antes de ampliar o modelo elétrico.
