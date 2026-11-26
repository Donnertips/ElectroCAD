# Arquitetura técnica

## Estado

Plano inicial sujeito a auditoria do código-fonte e às licenças da versão exata do QElectroTech. Não representa uma integração já realizada.

## Fundação CAD

1. Selecionar uma versão/tag/commit do QElectroTech.
2. Auditar o sistema de build, Qt exigido, compiladores e dependências.
3. Auditar licenças do código, bibliotecas e coleção de elementos.
4. Criar uma camada de personalização ElectroCAD com alterações rastreáveis.
5. Preservar formatos de projeto e criar testes de compatibilidade antes de os alterar.

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

## Modelo elétrico mínimo

Uma ligação identifica terminais concretos nas duas extremidades. Redes e derivações são explícitas. Continuidade interna só é aplicada quando existir modelo funcional verificado. Sem esse modelo, o comportamento é desconhecido.

## IEC e conteúdo normativo

A biblioteca de símbolos regista identificador, fonte, edição/versão, descrição, terminais, licença e estado de validação. Conteúdo oficial IEC 60617 depende de acesso e direitos adequados. Não reproduzir conteúdo normativo protegido sem autorização.
