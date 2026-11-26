# Avisos de terceiros e licenças

Inventário inicial do baseline upstream e do ambiente de compilação Windows, consultado em 26-11-2026. **Não é ainda um SBOM final do instalador ElectroCAD.** A lista final depende dos binários e recursos efetivamente distribuídos.

## Código principal e dados

### QElectroTech
- Origem: https://github.com/qelectrotech/qelectrotech-source-mirror
- Baseline: `b49ce16c42b99e458e38935f39b919d56582e54e` (0.200.1).
- Licença: GNU GPL versão 2 ou posterior, conforme LICENSE e cabeçalhos.
- Conservar copyright, licença e avisos de alterações. Para binários de obra derivada, disponibilizar o código-fonte correspondente e scripts de compilação/instalação exigidos pela GPL.
- A distribuição do ElectroCAD derivado terá de respeitar a GPL; não assumir que o produto pode ser fechado/proprietário sem uma análise jurídica e uma licença alternativa válida.

### Coleção de elementos QElectroTech
- Origem: https://github.com/qelectrotech/qelectrotech-elements
- Commit: `661f5e9ce5caa76277cafd3ebf0e0320fc4af229`; ficheiro `ELEMENTS.LICENSE`.
- Uso, edição e integração em esquemas elétricos permitidos sem condição, independentemente da licença final dos esquemas.
- Redistribuição da coleção fora de esquemas sob CC BY 3.0 com atribuição. Proibição de usar os ficheiros como amostras para construir modelos de aprendizagem automática.
- Não identificar a coleção como biblioteca oficial IEC 60617 validada.

## Bibliotecas obtidas como submódulos ou pelo CMake

| Componente | Revisão do baseline | Licença identificada / ação |
|---|---|---|
| pugixml | `27b68329de32cf9c601ca8eb6c588fd639960c40` (submódulo) | MIT; incluir aviso e texto integral. |
| SingleApplication | `a218603d76a55dddb65b84f2b49ecaa8efc074ea` (submódulo) | Licença permissiva com atribuição e inclusão do texto; conservar licença integral. |
| doxygen-awesome-css | `568f56cde6ac78b6dfcc14acd380b2e745c301ea` (submódulo) | MIT; só incluir no pacote se documentação/recursos correspondentes forem distribuídos. |
| Extra CMake Modules (ECM) | `7dd28cc56c339c3f8fb356f7c53c0e8f61433d81` (v6.10.0) | BSD 3-Clause, conforme documentação oficial KDE; componente de build, normalmente não runtime. |
| KCoreAddons | `c569f974dab24b4784ad186a3db4b76b2fa36612` (v6.10.0) | KDE Frameworks; obter e arquivar o ficheiro COPYING/COPYING.LIB exato da revisão antes de distribuição. A licença de distribuição deve ser confirmada no ficheiro da revisão usada. |
| KWidgetsAddons | `1abbed8a280d6626c59fb197f2c4667d2b1e7445` (v6.10.0) | KDE Frameworks; obter e arquivar o ficheiro COPYING/COPYING.LIB exato da revisão antes de distribuição. A licença de distribuição deve ser confirmada no ficheiro da revisão usada. |

Nota importante: o workflow Windows validado define `BUILD_KF=OFF`, pelo que usa os pacotes KDE instalados no MSYS2 em vez de compilar as revisões FetchContent acima. As versões efetivamente instaladas devem ser registadas por `pacman -Q` no workflow de release. Os commits acima descrevem a alternativa FetchContent fixada no CMake upstream, não provam que esses commits foram usados no build validado.

## Framework e bibliotecas do ambiente Windows

O workflow usa MSYS2 UCRT64 e instala explicitamente GCC, CMake, Ninja, Qt 6, KDE Frameworks, SQLite, hidapi e ferramentas auxiliares. A versão do pacote MSYS2 é móvel no workflow atual; por isso, o inventário abaixo é por família e não constitui identificação final de versões/ficheiros redistribuídos.

| Componente/família | Uso no build | Situação de licença |
|---|---|---|
| Qt 6 Base e módulos usados (Widgets, Gui, PrintSupport, Xml, Svg, Sql, Network, Concurrent, LinguistTools) | Runtime e ferramentas | Qt Community Edition usa sobretudo LGPLv3 com Qt GPL Exception e contém código de terceiros com licenças próprias; módulos específicos podem ser GPL. Confirmar módulo e ficheiros efetivamente empacotados. |
| Qt Pdf | Importação/funcionalidade PDF opcional | A presença do módulo tem de ser avaliada individualmente; não o assumir coberto por LGPL sem verificar a licença do pacote e versão exata. |
| Qt Qml / Declarative | Scripting opcional | Confirmar licença e dependências incluídas na versão efetiva do pacote. |
| KCoreAddons / KWidgetsAddons | Bibliotecas KDE usadas pelo programa | Arquivar avisos e licença das versões MSYS2 instaladas. |
| SQLite3 | Base de dados local | Núcleo SQLite dedicado ao domínio público; verificar extensões e patches do pacote. |
| hidapi | Suporte SpaceMouse HID opcional | O projeto oferece opções GPLv3, BSD-style e licença original; identificar a opção escolhida pelo pacote MSYS2 e incluir o texto aplicável. |
| GCC / libstdc++ / MinGW-w64 runtime | Toolchain e runtime | Rever GPL com GCC Runtime Library Exception, licenças do runtime MinGW-w64 e componentes auxiliares. Não presumir que o compilador é distribuído só por estar instalado no runner. |
| CMake / Ninja / pkg-config / Git | Ferramentas de build | Dependências de desenvolvimento; não distribuir no instalador salvo necessidade expressa. Registar licenças se forem redistribuídas. |

Qt oficial: LGPLv3 pode permitir aplicações com código próprio fechado apenas se todas as obrigações forem cumpridas, incluindo avisos, textos de licença, acesso ao código-fonte das bibliotecas Qt usadas e mecanismo de relink/substituição aplicável. Componentes Qt sob GPL podem impor GPL à aplicação combinada. Como o motor QElectroTech é GPL-2.0-or-later, a distribuição derivada já terá de ser analisada como obra GPL; não escolher componentes Qt GPL sem verificar compatibilidade entre licenças.

## Dependências transitivas

O pacote Qt Base MSYS2 consultado declara múltiplas dependências (incluindo ICU, FreeType, HarfBuzz, JPEG, PNG, OpenSSL, PCRE2, zlib, zstd, double-conversion e outras), cada uma com licença própria. O conjunto exato varia com a versão e com os módulos instalados. Não se considera concluída a auditoria transitiva até:
1. fixar versões dos pacotes MSYS2;
2. executar `pacman -Q` e exportar a lista completa de pacotes;
3. inspecionar as dependências runtime reais do executável e DLLs no pacote;
4. arquivar metadados SPDX/licenças e avisos de cada pacote distribuído;
5. gerar SBOM SPDX e verificar conflitos/obrigações.

O workflow atual só carrega o executável principal como artefacto de referência e não constrói um instalador portátil nem recolhe DLLs/runtime. Logo, ainda não existe uma lista definitiva de componentes redistribuídos.

## Símbolos e dados IEC

Não incluir uma base oficial IEC 60617 nem reproduções de símbolos protegidos sem confirmar direitos de acesso e utilização. Cada elemento próprio deve guardar proveniência, versão, licença e estado de validação. Símbolos comunitários não serão rotulados como oficiais IEC sem evidência.

## Processo obrigatório por release

Para cada componente, registar nome, versão, commit/hash, URL, licença SPDX, copyright, alterações locais, distribuição (build-only/runtime/data) e ficheiro de licença. Incluir os avisos no instalador e publicar o código-fonte correspondente exigido pelas licenças. A validação final deve ser feita sobre o pacote efetivamente distribuído, não apenas sobre o CMake.
