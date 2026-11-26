# Avisos de terceiros e licenças

Inventário inicial baseado nos ficheiros de licença e nos commits consultados em 26-11-2026. Revalidar em cada atualização de dependência e antes de cada distribuição.

## QElectroTech

- Origem: https://github.com/qelectrotech/qelectrotech-source-mirror
- Baseline auditado: `b49ce16c42b99e458e38935f39b919d56582e54e`
- Licença: GNU GPL versão 2 ou posterior, conforme LICENSE e cabeçalhos.
- Conservar avisos de copyright, texto da licença e avisos de alterações em ficheiros modificados.
- Para distribuição de binários de obra derivada, cumprir as obrigações GPL relativas ao código-fonte correspondente e aos scripts de compilação/instalação.
- A análise legal final deve ser feita antes da distribuição comercial.

## Coleção de elementos QElectroTech

- Origem: https://github.com/qelectrotech/qelectrotech-elements
- Commit no baseline: `661f5e9ce5caa76277cafd3ebf0e0320fc4af229`
- Ficheiro: `ELEMENTS.LICENSE`.
- Uso, edição e integração dos elementos em esquemas elétricos são permitidos sem condição, independentemente da licença final dos esquemas.
- Redistribuição da coleção ou de parte dela fora de um esquema elétrico está sujeita a CC BY 3.0 e respetiva atribuição.
- A licença declara que os elementos são fornecidos sem garantia.
- A licença proíbe utilizar os ficheiros associados como dados de amostra para construir modelos de aprendizagem automática.
- Esta coleção não deve ser identificada como biblioteca oficial IEC 60617 validada.

## pugixml

- Origem: https://github.com/zeux/pugixml
- Commit de submódulo no baseline: `27b68329de32cf9c601ca8eb6c588fd639960c40`.
- Licença observada: MIT (`LICENSE.md`).
- Incluir o aviso de copyright e o texto da licença nas distribuições que contenham o componente.

## SingleApplication

- Origem: https://github.com/itay-grudev/SingleApplication
- Commit de submódulo no baseline: `a218603d76a55dddb65b84f2b49ecaa8efc074ea`.
- Licença observada: permissiva, com cláusula expressa de atribuição e inclusão da licença.
- Preservar o aviso de copyright e o texto integral da licença.
- Os exemplos têm uma nota de licenciamento própria e não devem ser reutilizados sem revisão individual.

## doxygen-awesome-css

- Origem: https://github.com/jothepro/doxygen-awesome-css
- Commit de submódulo no baseline: `568f56cde6ac78b6dfcc14acd380b2e745c301ea`.
- Licença observada: MIT.
- Incluir o aviso de copyright e o texto da licença se for distribuído.

## KDE Frameworks

O CMake do QElectroTech obtém ECM, KCoreAddons e KWidgetsAddons por FetchContent ou encontra instalações do sistema. Os commits fixados no ficheiro CMake do baseline devem ser mantidos. Falta recolher e arquivar os ficheiros de licença desses projetos e das dependências transitivas incluídas no pacote final.

## Símbolos e dados IEC

Não incluir uma base oficial IEC 60617 nem reproduções de símbolos protegidos sem confirmar direitos de acesso e utilização. Cada elemento próprio deve guardar proveniência, versão, licença e estado de validação. Símbolos comunitários não serão rotulados como oficiais IEC sem evidência.

## Processo de atualização

Para cada componente, registar versão, commit, URL, licença, avisos de copyright, alterações locais e forma de distribuição. Gerar o inventário a partir das dependências realmente incluídas no instalador final, não apenas das dependências declaradas no código.
