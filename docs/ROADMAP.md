# Plano de desenvolvimento

As fases são sequenciais. Uma fase só fecha depois de implementação, testes reproduzíveis e revisão técnica.

## Fase 0 — Fundação e auditoria

- [x] Repositório, baseline upstream e estratégia de branches identificados.
- [x] Auditoria documental inicial do projeto, dependências e principais famílias de licenças.
- [x] Build upstream limpo reproduzido em CI Windows.
- [ ] Na fase de distribuição, fixar versões MSYS2, auditar DLLs/runtime empacotados e gerar SBOM SPDX final.

## Fase 1 — Integração do motor CAD elétrico

Estado: **integração inicial validada em CI Windows x64; integração funcional com o editor e persistência continuam em desenvolvimento. A base upstream Qt6/KF6 permanece experimental.**

- [x] Integração CMake hierárquica e alvo único QElectroTech validados.
- [x] Núcleo de terminais, ligações, redes e derivações.
- [x] Testes do modelo próprio e testes upstream executados em CI Windows.
- [x] Adaptador read-only da topologia nativa Diagram/Element/Terminal/Conductor integrado na main e validado nos runs 45901278849 e 45901297058.
- [ ] Integração do modelo com operações reais do editor, comandos e undo/redo.
- [ ] Sincronização segura entre alterações gráficas e modelo elétrico.
- [ ] Persistência e migração de IDs ElectroCAD.
- [ ] Deployment de Qt, recursos, traduções, elementos e modelos.
- [ ] Abrir, guardar e exportar projetos de referência com testes de ida e volta.
- [ ] Editor unifilar/multifilar e experiência de desenho.
- [ ] Potenciais e continuidade elétrica, incluindo modelos funcionais validados de aparelhos.
- [ ] Identificação/numeração de condutores, referências cruzadas e diagnóstico.
- [ ] Biblioteca IEC com proveniência e licenças verificadas.

## Fase 2 — Documentação e manuais

- [ ] Dossier técnico multipágina, capa, índice, legenda, revisões e templates.
- [ ] PDF exportado e validado.
- [ ] Relatórios ligados aos dados do projeto.

## Fase 3 — Equipamentos e fabricantes

- [ ] Base de equipamentos, referências comerciais, fichas técnicas e imagens com fontes.
- [ ] Lista de materiais gerada a partir do projeto.

## Fase 4 — Layout físico

- [ ] Placa, calhas DIN e canaletas em dimensões reais.
- [ ] Posicionamento, rotação, colisões, espaçamentos e avisos térmicos.
- [ ] 3D após validação geométrica 2D.

## Fase 5 — Engenharia e verificações

- [ ] Cálculos com entradas, hipóteses, fórmulas e unidades.
- [ ] Referência normativa e edição por verificação.
- [ ] Testes com casos de referência independentes.
- [ ] Avisos explícitos: apoio à engenharia, não certificação automática.

## Fase 6 — Plataforma central

- [ ] API, base de dados, autenticação, permissões e auditoria.
- [ ] Sincronização, conflitos e cópias de segurança.

## Fase 7 — Qualidade e distribuição

- [ ] Testes de regressão completos e build Windows reproduzível.
- [ ] Deployment, instalador e atualização.
- [ ] Inventário de licenças, avisos e SBOM do pacote.
- [ ] Assinatura e verificação do artefacto, quando disponível.

## Critério de fecho

Uma fase só é concluída quando todos os critérios aplicáveis têm implementação real, testes reproduzíveis, documentação e revisão de licenças. Itens por validar permanecem abertos.
