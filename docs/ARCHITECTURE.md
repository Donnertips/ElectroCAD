# Arquitetura técnica

## Estado

A integração CMake hierárquica do QElectroTech e os módulos iniciais ElectroCAD estão compilados e validados em CI Windows x64. O PR #3 foi integrado na `main` (commit `1ab608286c601b1a9e8c15f13c01ff1f540647c7`). A base upstream Qt6/KF6 continua experimental e ainda não é declarada versão de produção.

## Fundação CAD

- Motor base: QElectroTech 0.200.1-dev, Qt6/KF6, commit fixado em `UPSTREAM_BASELINE.md`.
- Uma única aplicação integrada; não criar wrapper nem segundo editor.
- Preservar formatos upstream e testar compatibilidade antes de os alterar.

## Módulos próprios previstos

- Project: identidade, páginas, revisões e metadados.
- ElectricalModel: terminais, ligações, nós, redes e continuidade.
- CrossReferences: associação de bobinas/contactos e referências entre folhas.
- Conductors: identificação, numeração e propriedades de cabos.
- Equipment: fabricantes, referências, características e fichas técnicas.
- Terminals: réguas de bornes, pontes e listas.
- PLCIO: endereços, canais, sinais e associação a equipamentos.
- PanelLayout: montagem 2D; 3D após validação geométrica.
- EngineeringChecks: cálculos com entradas, hipóteses, unidades e referências normativas.
- Documentation: relatórios e dossier técnico multipágina.
- DataServices: persistência, utilizadores e sincronização numa fase posterior.

## Requisitos transversais

- IDs estáveis para páginas, símbolos, terminais, redes e equipamentos.
- Separação entre representação gráfica e modelo elétrico.
- Histórico de alterações e migrações de dados.
- Testes unitários, integração, regressão e projetos de referência.
- Mensagens claras para dados incompletos ou não verificados.

## Modelo elétrico implementado

`src/electrocad/electricalmodel.*` implementa registo de terminais, ligações, redes e associação exclusiva de terminais a redes. Rejeita IDs vazios, terminais desconhecidos, auto-ligações e ligações duplicadas. O módulo e os testes próprios passaram CI Windows nos runs 45881881930, 45901278849 e 45901297058.

## Adaptador nativo QElectroTech

`QetDiagramAdapter` constrói um snapshot read-only a partir de `Diagram`, `Element`, `Terminal` e `Conductor`. Usa UUIDs estáveis, considera apenas condutores explícitos e agrupa terminais ligados em componentes conexos, incluindo derivações. Não infere continuidade interna dos aparelhos, não altera o diagrama e não substitui os algoritmos de potencial QET.

O adaptador passou compilação, testes do workflow e verificação do executável nos runs 45901278849 e 45901297058. Ainda não existe teste funcional de edição/sincronização bidirecional nem de persistência ElectroCAD.

## Limites e próximos passos

Continuam por validar deployment de Qt, recursos, traduções, elementos e modelos; abrir/guardar/exportar projetos reais; integração com comandos do editor e undo/redo; potenciais e continuidade interna validada; identificação de condutores; referências cruzadas; diagnóstico e biblioteca IEC com proveniência/licenças verificadas.

## IEC e conteúdo normativo

A biblioteca de símbolos deverá registar identificador, fonte, edição/versão, descrição, terminais, licença e estado de validação. Conteúdo oficial IEC 60617 depende de acesso e direitos adequados. Não reproduzir conteúdo normativo protegido sem autorização.
