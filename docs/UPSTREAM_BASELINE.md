# Referência técnica upstream — QElectroTech

Data da verificação: 26-11-2026

## Commit de referência para auditoria/build

- Repositório: https://github.com/qelectrotech/qelectrotech-source-mirror
- Branch observada: `master`
- Commit completo: `b49ce16c42b99e458e38935f39b919d56582e54e`
- Data do commit: 2026-11-26 09:26:17 UTC
- Mensagem: merge de verificações adicionais de projeto (cabos, referência de equipamento em falta e prompts sem resposta).
- Árvore Git: `6ca1d036260e552dbc1fc1729cb580aec92822b3`
- Assinatura do commit: GitHub indica verificação válida.
- Versão declarada no CMake: 0.200.1.

Este SHA fica registado como **baseline reprodutível para auditoria e integração experimental**, não como decisão definitiva de versão de produção. É uma revisão da linha de desenvolvimento/nightly; a escolha de produção exige comparar com a linha estável e executar testes de compatibilidade do ElectroCAD.

## Submódulos fixados no commit

Os seguintes gitlinks foram lidos diretamente da árvore Git do commit acima:

| Caminho | Repositório | Commit fixado |
|---|---|---|
| `pugixml` | https://github.com/zeux/pugixml | `27b68329de32cf9c601ca8eb6c588fd639960c40` |
| `SingleApplication` | https://github.com/itay-grudev/SingleApplication | `a218603d76a55dddb65b84f2b49ecaa8efc074ea` |
| `elements` | https://github.com/qelectrotech/qelectrotech-elements | `661f5e9ce5caa76277cafd3ebf0e0320fc4af229` |
| `doxygen-awesome-css` | https://github.com/jothepro/doxygen-awesome-css | `568f56cde6ac78b6dfcc14acd380b2e745c301ea` |

Não substituir estes SHAs por referências móveis como `main`, `master` ou tags sem registar e rever o novo commit.

## Licenças identificadas

| Componente | Condições observadas | Implicação para ElectroCAD |
|---|---|---|
| Código QElectroTech | GNU GPL versão 2 ou posterior, conforme cabeçalhos e LICENSE | Distribuição de obra derivada deve cumprir GPL; conservar avisos e fornecer código-fonte correspondente e scripts de build/instalação exigidos. |
| Coleção de elementos QET | ELEMENTS.LICENSE: uso, edição e integração em esquemas elétricos permitidos sem condição, independentemente da licença final do esquema; redistribuição da coleção fora de esquemas sob CC BY 3.0 | Pode ser utilizada em esquemas. Se a coleção ou parte dela for distribuída separadamente, atribuir autoria conforme CC BY 3.0 e preservar o aviso. Não apresentar a coleção como IEC 60617 oficial. |
| pugixml | MIT no ficheiro LICENSE.md consultado | Preservar aviso de copyright e texto da licença. |
| SingleApplication | Licença permissiva com texto MIT-like e cláusula explícita de atribuição/inclusão da licença; exemplos têm nota própria | Conservar licença e atribuição; rever exemplos separadamente antes de reutilizar código deles. |
| doxygen-awesome-css | MIT no ficheiro LICENSE consultado | Preservar aviso de copyright e texto da licença. |
| KDE Frameworks (ECM, KCoreAddons, KWidgetsAddons) | Obtidos por FetchContent nos commits fixados no CMake; inventário legal detalhado ainda pendente | Registar os commits exatos e recolher os respetivos ficheiros de licença antes de distribuir o pacote. |

### Restrição explícita da coleção de elementos

O `ELEMENTS.LICENSE` declara que os ficheiros associados não podem ser utilizados como dados de amostra para construir modelos de aprendizagem automática. Esta condição deve ser respeitada. A licença também declara que a coleção é fornecida sem garantia.

## Evidência de compilação Windows upstream

No commit `b49ce16c42b99e458e38935f39b919d56582e54e`, o repositório upstream tem uma execução GitHub Actions:

- Workflow Windows Build: https://github.com/qelectrotech/qelectrotech-source-mirror/actions/runs/45806034743
- Resultado: concluído com sucesso.
- Job: `build-windows-qt6`.
- Passos confirmados como bem-sucedidos: checkout recursivo, instalação de dependências MSYS2 UCRT64, configuração CMake, compilação Ninja, testes unitários, verificação do executável, deployment de DLLs e criação do pacote.
- Workflow Windows MSI: https://github.com/qelectrotech/qelectrotech-source-mirror/actions/runs/45810890238
- Resultado: concluído com sucesso.
- Workflow Linux build e testes: https://github.com/qelectrotech/qelectrotech-source-mirror/actions/runs/45791966123
- Resultado: concluído com sucesso.

O release upstream `nightly-qt6` publicou para este commit um instalador Windows x64:
`Installer_QElectroTech-0.200.1-qt6-r12569-b49ce16c4_x86_64-win64-1.exe`

SHA-256 publicado pelo release:
`7ff2ebc7353163838e8cfa7137180a4c1db211479a67649b84c3546aa221ea7b`

Isto demonstra que o upstream compilou e empacotou esta revisão no seu próprio CI. **Não demonstra que o ElectroCAD foi compilado**, nem que este instalador seja o ElectroCAD. Não o distribuir como produto ElectroCAD.

## Perfil de compilação Windows recomendado para a primeira reprodução

A pipeline oficial desta revisão usa:
- Windows runner;
- MSYS2 UCRT64;
- MinGW-w64 GCC;
- CMake + Ninja;
- Qt 6;
- KF6 CoreAddons/WidgetsAddons fornecidos pelo MSYS2;
- SQLite3;
- QtPdf, Qt Declarative e hidapi;
- checkout com submódulos recursivos.

O guia INSTALL.md também documenta um caminho MSVC, mas a pipeline oficial bem-sucedida identificada nesta revisão usa MSYS2 UCRT64/MinGW. Para reduzir variáveis, a primeira reprodução do ElectroCAD deve começar pelo mesmo toolchain e só depois avaliar MSVC.

## Pendências antes de fixar a versão de produção

- Comparar o baseline 0.200.1 com a versão estável publicada.
- Rever o estado de manutenção e compatibilidade da revisão.
- Reproduzir o build no repositório ElectroCAD, com workflow próprio e sem alterações ao upstream.
- Executar testes de regressão de abertura/guarda dos formatos QET.
- Completar o inventário de licenças de KF6 e das dependências transitivas efetivamente distribuídas.
- Definir estratégia de integração: fork/subtree/submodule ou upstream remoto fixado. Não copiar código para o repositório ElectroCAD antes de fechar esta decisão.
