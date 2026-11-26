# Política de branches, versões e releases

Estado: política inicial adotada para o desenvolvimento do ElectroCAD.

## Branches

- `main`: ramo principal, sempre compilável; recebe alterações por Pull Request.
- `feature/<descrição-curta>`: novas funcionalidades.
- `fix/<descrição-curta>`: correções sem urgência de release.
- `hotfix/<descrição-curta>`: correções urgentes sobre uma versão publicada.
- `release/<MAJOR.MINOR.PATCH>`: estabilização temporária de uma release, apenas quando houver necessidade real de preparar uma distribuição.

Não desenvolver diretamente em `main), salvo alterações documentais pequenas e urgentes. Não manter branches permanentes por plataforma.

## Pull Requests e integração

Cada PR deve:
1. indicar objetivo, âmbito e impacto nos formatos de projeto;
2. incluir testes automatizados para alterações funcionais;
3. passar o workflow Windows x64 e os testes aplicáveis;
4. atualizar documentação, avisos de terceiros e migrações quando necessário;
5. identificar alterações a dependências e respetivos commits/licenças.

Não aceitar PR com testes falhados, dependências sem versão/commit identificável ou alterações de formato sem teste de compatibilidade. Exigir revisão antes de integrar código funcional. Ativar proteção de `main` no GitHub (PR obrigatório, checks obrigatórios e impedir force-push/delete) quando a configuração de repositório estiver operacional.

## Versionamento

Usar Semantic Versioning: `MAJOR.MINOR.PATCH`.

- `0.y.z`: desenvolvimento inicial; a API e os formatos podem evoluir com migrações documentadas.
- `1.0.0`: primeira versão considerada estável para utilização profissional, após cumprir os critérios de qualidade, compatibilidade, testes e licenças.
- `PATCH`: correções compatíveis.
- `MINOR`: novas funcionalidades compatíveis.
- `MAJOR`: alterações incompatíveis a API, formatos ou comportamento.

Tags anotadas e imutáveis: `vX.Y.Z`. Não mover nem reutilizar tags. Pré-lançamentos usam `vX.Y.Z-alpha.N`, `beta.N` ou `rc.N`.

A versão do ElectroCAD é independente da versão upstream QElectroTech. Registar sempre o SHA upstream e os SHAs de submódulos/dependências no manifesto da release.

## Critérios de release

Uma release só pode ser publicada quando:
- build limpo Windows x64 e testes relevantes passam;
- testes de abertura/gravação e migração de projetos passam;
- o instalador é testado numa máquina Windows limpa;
- o inventário de componentes distribuídos e respetivos textos de licença está completo;
- código-fonte correspondente, scripts de build/instalação e instruções exigidos pelas licenças acompanham a distribuição;
- changelog, limitações conhecidas e instruções de atualização estão publicados;
- artefactos têm SHA-256 e, quando disponível, assinatura digital.

## Artefactos e proveniência

Cada release deve incluir:
- instalador x64 e respetivo SHA-256;
- código-fonte da versão ElectroCAD e referências upstream exatas;
- `THIRD_PARTY_NOTICES.md`, cópias das licenças e SBOM (preferencialmente SPDX);
- notas da versão e instruções de atualização;
- evidência do workflow que produziu os artefactos.

O executável de referência QElectroTech produzido pelo workflow de auditoria nunca deve ser publicado como se fosse o ElectroCAD.

## Dependências e segurança

Fixar dependências por commit ou versão imutável. Não usar branches móveis ou tags mutáveis em builds de release. Guardar versões e hashes dos pacotes de toolchain e dependências do ambiente. Atualizações de segurança podem ser integradas por hotfix, mantendo registo de proveniência.

## Estado atual

Esta política não declara que exista já uma release ElectroCAD. O repositório continua na fase de integração do motor CAD; a política passa a aplicar-se quando começarem as alterações de código e os primeiros artefactos próprios.
