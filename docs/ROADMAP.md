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
- [x] Reproduzir compilação limpa do projeto de origem no workflow Windows do ElectroCAD; build, testes unitários e verificação do executável concluídos com sucesso (run 45821375354).
- [x] Definir política de branches, tags e releases (ver `RELEASE_POLICY.md`).

## Fecho da fundação

A política de desenvolvimento/release e o inventário preliminar de dependências estão documentados. A auditoria legal específica do instalador e a SBOM final ficam corretamente adiadas para a fase de distribuição, quando os componentes realmente incluídos forem conhecidos. O workflow Windows passa a arquivar também a lista de pacotes MSYS2 instalados.

## Fase 1 — Motor CAD elétrico

Estado: **próxima fase — integração da base QElectroTech 0.200.1 (Qt6/KF6), fixada por SHA e ainda experimental**. A integração só fecha após testes de formatos, regressão e inventário de licenças.

- [ ] Integrar a base CAD auditada.
- [ ] Editor unifilar e multifilar.
- [ ] Símbolos com terminais e pontos de ligação.
- [ ] Ligações terminal-a-terminal, nós e derivações.
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
