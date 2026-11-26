# Ambiente de compilação Windows

## Objetivo

Documentar um ambiente reprodutível para compilar a versão de origem selecionada e, posteriormente, o ElectroCAD.

## Ferramentas a confirmar

- Git.
- CMake compatível com a versão selecionada.
- Qt na versão exigida pelo commit selecionado.
- Visual Studio / MSVC x64 compatível.
- Windows SDK exigido pelas dependências.

Não escolher versões arbitrárias antes de confirmar os requisitos do commit.

## Processo previsto

1. Clonar o repositório de origem e selecionar o commit fixado.
2. Configurar Qt e compilador segundo a documentação dessa versão.
3. Configurar com CMake.
4. Compilar em Release.
5. Executar os testes disponíveis.
6. Registar versões, comandos e resultados.
7. Só depois preparar o pacote/instalador ElectroCAD.

## Estado atual

Ainda não existe neste repositório uma compilação Windows validada. Este documento é um plano, não uma confirmação de ambiente instalado ou build bem-sucedida.
