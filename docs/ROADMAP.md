# Plano de desenvolvimento

As fases são sequenciais. Uma fase só fecha depois de implementação, testes reproduzíveis e revisão técnica.

## Fase 0 — Fundação e auditoria

- [x] Repositório ElectroCAD existente identificado.
- [x] Registar commit upstream de referência para auditoria/build experimental (não é ainda a versão de produção; ver `UPSTREAM_BASELINE.md`).
- [x] Comparar a versão estável publicada com a linha Qt6/KF6 (decisão de base registada em UPSTREAM_BASELINE.md; validação de compatibilidade do ElectroCAD continua pendente).
- [x] Auditoria documental inicial do README, CMakeLists.txt e GPL-2.0 (ver `QELECTROTECH_AUDIT.md`).
- [x] Identificação documental dos quatro submódulos e das dependências CMake (ver `QELECTROTECH_AUDIT.md`).
- [x] Inventário inicial das dependências declaradas, toolchain Windows e principais famílias de licenças (ver `THIRD_PARTY_NOTICES.md`).
- [ ] Na fase de distribuição, fixar versões MSYS2, auditar DLLs/runtime efetivamente empacotados e gerar SBOM SPDX final.
- [x] Reproduzir compilação limpa do projeto de origem no workflow Windows do ElectroCAD; build e testes unitários concluídos no run 45821375354.
- [x] Definir política de branches, tags e releases (ver `RELEASE_POLICY.md`).

## Fase 1 — Integração do motor CAD elétrico

Estado: **em curso — integração CMake e build Windows x64 validados no CI do commit `49cef6c21e89a25895ecf14656e52d1b5acfd2d5`; a base upstream permanece experimental.**

- [x] Criar branch de trabalho `feature/qelectrotech-integration`.
- [x] Auditar o CMake upstream e identificar os alvos `qelectrotech_objects` e `qelectrotech`.
- [x] Documentar a estratégia de aplicação única e critérios de aceitação (ver `INTEGRATION_STRATEGY.md`).
- [x] Validar configuração CMake hierárquica e alvo integrado no workflow Windows (checkout upstream fixado pelo workflow; adoção de submódulo Git ainda pendente).
- [x] Implementar o primeiro núcleo C++ de terminais e ligações e adicioná-lo ao alvo do executável QElectroTech.
- [x] Build Windows x64, testes upstream e testes do módulo próprio no run 45869976768 (commit `49cef6c...`).
- [ ] Confirmar deployment de Qt, recursos, traduções, elementos e modelos.
- [ ] Testar abrir, guardar e exportar projetos de referência.
- [ ] Editor unifilar e multifilar.
- [ ] Símbolos com terminais e pontos de ligação.
- [ ] Ligações terminal-a-terminal, nós e derivações (API inicial de redes/associação de terminais em desenvolvimento; CI pendente).
- [ ] Redes, potenciais e continuidade.
- [ ] Identificação e numeração de condutores.
- [ ] Modelos verificados de continuidade interna.
- [ ] Bobinas/contactos e referências cruzadas.
- [ ] Diagnóstico de ligações pendentes e terminais não ligados.
- [ ] Guardar/abrir e exportar com testes de regressão.
- [ ] Biblioteca IEC com proveniência e licenças verificadas.

## Fase 2 — Documentação e manuais

- [ ] Dossier técnico multipágina.
- [ ] Capa, índice, legenda, revisões e templates.
- [ ] PDF exportado e validado.
- [ ] Relatórios ligados aos dados do projeto.

## Fase 3 — Equipamentos e fabricantes

- [ ] Base de equipamentos e referências comerciais.
- [ ] Fichas técnicas e imagens com fontes.
- [ ] Lista de materiais gerada a partir do projeto.

## Fase 4 — Layout físico

- [ ] Placa, calhas DIN e canaletas em dimensões reais.
- [ ] Posicionamento, rotação e colisões.
- [ ] Regras de espaçamento e avisos térmicos.
- [ ] 3D após validação do modelo 2D.

## Fase 5 — Engenharia e verificações

- [ ] Cálculos com entradas, hipóteses, fórmulas e unidades.
- [ ] Referência normativa e edição por verificação.
- [ ] Testes com casos de referência independentes.
- [ ] Avisos explícitos: apoio à engenharia, não certificação automática.

## Fase 6 — Plataforma central

- [ ] API e base de dados.
- [ ] Autenticação, permissões e auditoria.
- [ ] Sincronização, conflitos e cópias de segurança.

## Fase 7 — Qualidade e distribuição

- [ ] Testes de regressão completos.
- [ ] Build Windows reproduzível.
- [ ] Instalador e atualização.
- [ ] Inventário de licenças e avisos no pacote.
- [ ] Assinatura e verificação do artefacto, quando disponível.

## Critério de fecho

Uma fase só é concluída quando todos os critérios aplicáveis têm implementação real, testes reproduzíveis, documentação e revisão de licenças. Itens por validar permanecem abertos.
