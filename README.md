# ElectroCAD

Plataforma CAD elétrica para documentação, engenharia e projeto de quadros elétricos.

## Objetivo

O ElectroCAD será desenvolvido a partir de uma auditoria e adaptação do QElectroTech, complementado por módulos próprios. A reutilização fica condicionada à confirmação da licença da versão escolhida, das dependências e das coleções de elementos.

## Estado

**Preparação do repositório.** Este repositório ainda não contém uma aplicação ElectroCAD compilável nem uma integração do código-fonte do QElectroTech.

## Arquitetura prevista

- Motor CAD: QElectroTech (C++ / Qt), após auditoria técnica e de licenças.
- Módulos próprios: engenharia elétrica, equipamentos, bornes/cablagem, layout, documentação e gestão.
- Dados de projeto: preservar compatibilidade e definir migrações antes de alterar formatos existentes.
- Plataforma alvo inicial: Windows 64-bit.

## Documentação

- [Auditoria técnica do QElectroTech](docs/QELECTROTECH_AUDIT.md)
- [Baseline upstream e commits fixados](docs/UPSTREAM_BASELINE.md)
- [Workflow de compilação de referência](.github/workflows/qelectrotech-upstream-build.yml)
- [Arquitetura](docs/ARCHITECTURE.md)
- [Plano de desenvolvimento](docs/ROADMAP.md)
- [Política de branches, versões e releases](docs/RELEASE_POLICY.md)
- [Avisos de terceiros e licenças](THIRD_PARTY_NOTICES.md)
- [Ambiente Windows](build-windows/README.md)

## Princípios

1. Não apresentar símbolos genéricos como símbolos IEC validados.
2. Não inventar dados técnicos de fabricantes.
3. Não declarar conformidade normativa automática sem validação técnica.
4. Preservar avisos de copyright e cumprir as licenças de todo o código e conteúdo reutilizado.
5. Marcar funcionalidades como concluídas apenas depois de testes reproduzíveis.

## Distribuição

As condições de distribuição dependem das licenças efetivamente incorporadas. Consultar os avisos de terceiros antes de distribuir binários ou código-fonte.
