# Arquitetura técnica

## Estado

A estratégia de integração está documentada em [INTEGRATION_STRATEGY.md](INTEGRATION_STRATEGY.md). A integração do código ainda não foi executada nem validada num build hierárquico.

## Fundação CAD

- Motor base: QElectroTech 0.200.1-dev, Qt6/KF6, commit fixado em `UPSTREAM_BASELINE.md`; experimental, não declarado estável para produção.
- Estratégia candidata: submódulo upstream + CMake de topo ElectroCAD + módulos próprios ligados ao alvo de objetos QElectroTech, formando um único executável.
- Se o build hierárquico não for compatível, usar fork de integração com histórico upstream explícito; não criar um segundo executável.
- Alterações upstream devem ser pequenas, rastreáveis e testadas.
- Preservar formatos de projeto e criar testes de compatibilidade antes de os alterar.

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

## Primeiro módulo implementado (em validação)

O diretório `src/electrocad/` contém o primeiro núcleo C++ do modelo elétrico. Regista terminais identificados por componente e terminal e aceita ligações apenas entre terminais registados. Rejeita identificadores vazios, terminais desconhecidos, auto-ligações e ligações duplicadas sem depender da ordem dos extremos. O código é incluído no alvo do executável QElectroTech; os testes próprios são registados no CTest. Esta implementação ainda não está validada por build CI nem representa um modelo completo de redes, derivações ou continuidade.

## Modelo elétrico mínimo

Uma ligação identifica terminais concretos nas duas extremidades. Redes e derivações são explícitas. Continuidade interna só é aplicada quando existir modelo funcional verificado. Sem esse modelo, o comportamento é desconhecido.

## IEC e conteúdo normativo

A biblioteca de símbolos regista identificador, fonte, edição/versão, descrição, terminais, licença e estado de validação. Conteúdo oficial IEC 60617 depende de acesso e direitos adequados. Não reproduzir conteúdo normativo protegido sem autorização.
