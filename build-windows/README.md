# Ambiente de compilação Windows

## Objetivo

Reproduzir de forma controlada a compilação do QElectroTech selecionado e, depois, compilar o ElectroCAD.

## Baseline de referência

- Repositório upstream: https://github.com/qelectrotech/qelectrotech-source-mirror
- Commit: `b49ce16c42b99e458e38935f39b919d56582e54e`
- Toolchain da pipeline upstream validada: Windows x64, MSYS2 UCRT64, MinGW-w64 GCC, CMake, Ninja e Qt 6.
- Ver [baseline e evidência CI](../docs/UPSTREAM_BASELINE.md).

## Primeira reprodução automatizada

Foi adicionado o workflow [qelectrotech-upstream-build.yml](../.github/workflows/qelectrotech-upstream-build.yml). Este workflow obtém o commit fixado com submódulos recursivos, instala as dependências no runner Windows, compila, executa testes e publica temporariamente o executável upstream como artefacto de CI.

A criação do workflow está confirmada; a sua execução no repositório ElectroCAD ainda tem de ser observada e validada. A evidência de build bem-sucedida atualmente disponível pertence ao CI oficial do QElectroTech, não ao CI do ElectroCAD.

## Toolchain de referência

A pipeline oficial do commit selecionado usa:
- Windows runner;
- MSYS2 UCRT64;
- MinGW-w64 GCC;
- Qt 6 e Qt6::GuiPrivate;
- KF6 CoreAddons e WidgetsAddons;
- SQLite3;
- CMake e Ninja;
- QtPdf, Qt Declarative e hidapi.

Esta é a primeira via a reproduzir para reduzir diferenças face ao upstream. O guia upstream também documenta MSVC x64; essa variante será avaliada depois de a referência MinGW estar reproduzida.

## Critérios para considerar a referência validada

1. Checkout do commit SHA exato e dos submódulos recursivos.
2. Configuração CMake sem erros.
3. Build Release concluído.
4. Testes unitários concluídos com sucesso.
5. Executável presente e com dependências verificadas.
6. Registo dos logs, versões de ferramentas e hashes dos artefactos.

## Estado

Ainda não existe uma compilação ElectroCAD validada nem um executável ElectroCAD. O artefacto da pipeline de referência, quando produzido, será apenas o executável QElectroTech upstream e não deve ser apresentado como produto ElectroCAD.
