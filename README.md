# Atividade Prática: De MIPS para WebAssembly

Disciplina de Arquitetura e Organização de Computadores (UFRR/DCC). O projeto implementa, em C, detecção de overflow de 32 bits com sinal para soma, subtração e multiplicação — a mesma lógica que o MIPS resolve em hardware (`add`/`addu`) —, verifica formalmente essa lógica com **Map2Check**, compila para **WebAssembly** e expõe o resultado numa interface web que anima a operação bit a bit.

## Estrutura do repositório

| Arquivo | Descrição |
|---|---|
| `aritmetica.c` | Código-fonte em C: `soma`/`sub`/`mul` (versões vulneráveis a overflow) e `soma_segura`/`sub_segura`/`mul_segura` (com detecção via análise de sinal em complemento de dois). |
| `aritmetica.wasm` | Módulo compilado a partir de `aritmetica.c`, alvo `wasm32`. |
| `aritmetica.wat` | Representação textual do `.wasm` (gerada com `wasm2wat`), usada para comparar as instruções da máquina de pilha do WebAssembly com o assembly MIPS. |
| `index.html` | Interface web: carrega o `.wasm`, recebe dois operandos e a operação, e anima a conversão para binário e a propagação de carry/borrow bit a bit, sinalizando overflow visualmente. |
| `teste_soma.c`, `teste_soma_segura.c`, `teste_sub.c`, `teste_sub_segura.c`, `teste_mul.c`, `teste_mul_segura.c` | Arquivos-driver usados para verificar cada função individualmente com o Map2Check (cada um define um `main()` com `__VERIFIER_nondet_int()`, necessário porque a ferramenta não analisa arquivos sem ponto de entrada). |
| `teste_soma.c.testcase` | Caso de teste concreto gerado pelo Klee durante uma das execuções do Map2Check sobre `teste_soma.c`. |
| `Containerfile` | Imagem de build com `clang` (alvo `wasm32`) e `wabt` (`wasm2wat`), usada na Etapa C. |
| `Containerfile.map2check` | Imagem `ubuntu:20.04` com a dependência `libsqlite3-0`, necessária para rodar o binário oficial do Map2Check (2019) num ambiente moderno. |

## Como compilar (Etapa C)

Requer `clang` com suporte a `wasm32` e `wasm2wat` (pacote `wabt`). Se preferir isolar em contêiner, use o `Containerfile` deste repositório:

```bash
podman build -t aoc-wasm -f Containerfile .
podman run --rm -v "$PWD":/work:Z aoc-wasm bash -c "
  clang --target=wasm32 -nostdlib -Wl,--no-entry -Wl,--export-all -o aritmetica.wasm aritmetica.c
  wasm2wat aritmetica.wasm -o aritmetica.wat
"
```

## Como rodar a interface web (Etapa D)

Abrir `index.html` direto como arquivo local **não funciona** — `fetch('aritmetica.wasm')` é bloqueado por CORS em `file://`. É preciso servir por HTTP:

```bash
python3 -m http.server 8080
```

Depois acesse `http://localhost:8080/` no navegador. Escolha a operação (soma, subtração ou multiplicação), informe os dois operandos e clique em **Calcular & Animar**.

## Como verificar com o Map2Check (Etapa B)

O binário oficial é de 2019 (`v7.3.1.2019-11.27.140ba2d2`) e exige um ambiente Ubuntu 20.04 com `libsqlite3-0`:# Atividade Prática: De MIPS para WebAssembly

Disciplina de Arquitetura e Organização de Computadores (UFRR/DCC). O projeto implementa, em C, detecção de overflow de 32 bits com sinal para soma, subtração e multiplicação — a mesma lógica que o MIPS resolve em hardware (`add`/`addu`) —, verifica formalmente essa lógica com **Map2Check**, compila para **WebAssembly** e expõe o resultado numa interface web que anima a operação bit a bit.

## Estrutura do repositório

| Arquivo | Descrição |
|---|---|
| `aritmetica.c` | Código-fonte em C: `soma`/`sub`/`mul` (versões vulneráveis a overflow) e `soma_segura`/`sub_segura`/`mul_segura` (com detecção via análise de sinal em complemento de dois). |
| `aritmetica.wasm` | Módulo compilado a partir de `aritmetica.c`, alvo `wasm32`. |
| `aritmetica.wat` | Representação textual do `.wasm` (gerada com `wasm2wat`), usada para comparar as instruções da máquina de pilha do WebAssembly com o assembly MIPS. |
| `index.html` | Interface web: carrega o `.wasm`, recebe dois operandos e a operação, e anima a conversão para binário e a propagação de carry/borrow bit a bit, sinalizando overflow visualmente. |
| `teste_soma.c`, `teste_soma_segura.c`, `teste_sub.c`, `teste_sub_segura.c`, `teste_mul.c`, `teste_mul_segura.c` | Arquivos-driver usados para verificar cada função individualmente com o Map2Check (cada um define um `main()` com `__VERIFIER_nondet_int()`, necessário porque a ferramenta não analisa arquivos sem ponto de entrada). |
| `teste_soma.c.testcase` | Caso de teste concreto gerado pelo Klee durante uma das execuções do Map2Check sobre `teste_soma.c`. |
| `Containerfile` | Imagem de build com `clang` (alvo `wasm32`) e `wabt` (`wasm2wat`), usada na Etapa C. |
| `Containerfile.map2check` | Imagem `ubuntu:20.04` com a dependência `libsqlite3-0`, necessária para rodar o binário oficial do Map2Check (2019) num ambiente moderno. |

## Como compilar (Etapa C)

Requer `clang` com suporte a `wasm32` e `wasm2wat` (pacote `wabt`). Se preferir isolar em contêiner, use o `Containerfile` deste repositório:

```bash
podman build -t aoc-wasm -f Containerfile .
podman run --rm -v "$PWD":/work:Z aoc-wasm bash -c "
  clang --target=wasm32 -nostdlib -Wl,--no-entry -Wl,--export-all -o aritmetica.wasm aritmetica.c
  wasm2wat aritmetica.wasm -o aritmetica.wat
"
```

## Como rodar a interface web (Etapa D)

Abrir `index.html` direto como arquivo local **não funciona** — `fetch('aritmetica.wasm')` é bloqueado por CORS em `file://`. É preciso servir por HTTP:

```bash
python3 -m http.server 8080
```

Depois acesse `http://localhost:8080/` no navegador. Escolha a operação (soma, subtração ou multiplicação), informe os dois operandos e clique em **Calcular & Animar**.

## Como verificar com o Map2Check (Etapa B)

O binário oficial é de 2019 (`v7.3.1.2019-11.27.140ba2d2`) e exige um ambiente Ubuntu 20.04 com `libsqlite3-0`:

```bash
podman build -t aoc-map2check -f Containerfile.map2check .
curl -L -o map2check.zip "https://github.com/hbgit/Map2Check/releases/download/v7.3.1.2019-11.27.140ba2d2/map2check-rc-v7.3-svcomp20.zip"
mkdir -p map2check_bin && unzip map2check.zip -d map2check_bin

podman run --rm -it -v "$PWD/map2check_bin":/opt/map2check_bin:Z -v "$PWD":/work:Z aoc-map2check bash -c "
  cd /opt/map2check_bin/map2check
  ./map2check --check-overflow /work/teste_soma.c
"
```

> A flag correta é `--check-overflow` (não `--overflow`). Arquivos **sem `main()`** fazem a ferramenta falhar com `std::bad_alloc` — por isso os `teste_*.c` existem como arquivos-driver separados de `aritmetica.c`. Em funções com divisão (`mul_segura`), adicione `--timeout 60` se a verificação não terminar — divisão totalmente simbólica é difícil para o solver SMT.

## Resultados obtidos com o Map2Check

| Função | Resultado |
|---|---|
| `soma` | `VERIFICATION FAILED` (overflow confirmado) |
| `soma_segura` | `VERIFICATION FAILED` na operação bruta interna — a instrumentação da ferramenta não sabe que a função já sinaliza o overflow via `*teve_overflow` |
| `sub` | `VERIFICATION FAILED` (overflow confirmado) |
| `sub_segura` | Mesmo caso de `soma_segura` |
| `mul` | `VERIFICATION FAILED` (overflow confirmado) |
| `mul_segura` | `VERIFICATION UNKNOWN` (timeout — divisão simbólica) |

## Declaração de uso de IA generativa

Conforme a seção 8 do enunciado: ferramentas de IA generativa foram usadas para **explicar conceitos de WebAssembly** (semântica de máquina de pilha, `local.get`/`i32.add`) e **auxiliar no HTML/CSS/JS** da interface (Etapa D). A lógica de detecção de overflow em C (Etapa A) e a interpretação dos resultados do Map2Check (Etapa B) foram elaboradas pelos alunos, conforme exigido para a defesa oral.


```bash
podman build -t aoc-map2check -f Containerfile.map2check .
curl -L -o map2check.zip "https://github.com/hbgit/Map2Check/releases/download/v7.3.1.2019-11.27.140ba2d2/map2check-rc-v7.3-svcomp20.zip"
mkdir -p map2check_bin && unzip map2check.zip -d map2check_bin

podman run --rm -it -v "$PWD/map2check_bin":/opt/map2check_bin:Z -v "$PWD":/work:Z aoc-map2check bash -c "
  cd /opt/map2check_bin/map2check
  ./map2check --check-overflow /work/teste_soma.c
"
```

> A flag correta é `--check-overflow` (não `--overflow`). Arquivos **sem `main()`** fazem a ferramenta falhar com `std::bad_alloc` — por isso os `teste_*.c` existem como arquivos-driver separados de `aritmetica.c`. Em funções com divisão (`mul_segura`), adicione `--timeout 60` se a verificação não terminar — divisão totalmente simbólica é difícil para o solver SMT.

## Resultados obtidos com o Map2Check

| Função | Resultado |
|---|---|
| `soma` | `VERIFICATION FAILED` (overflow confirmado) |
| `soma_segura` | `VERIFICATION FAILED` na operação bruta interna — a instrumentação da ferramenta não sabe que a função já sinaliza o overflow via `*teve_overflow` |
| `sub` | `VERIFICATION FAILED` (overflow confirmado) |
| `sub_segura` | Mesmo caso de `soma_segura` |
| `mul` | `VERIFICATION FAILED` (overflow confirmado) |
| `mul_segura` | `VERIFICATION UNKNOWN` (timeout — divisão simbólica) |

## Declaração de uso de IA generativa

Conforme a seção 8 do enunciado: ferramentas de IA generativa foram usadas para **explicar conceitos de WebAssembly** (semântica de máquina de pilha, `local.get`/`i32.add`) e **auxiliar no HTML/CSS/JS** da interface (Etapa D). A lógica de detecção de overflow em C (Etapa A) e a interpretação dos resultados do Map2Check (Etapa B) foram elaboradas pelos alunos, conforme exigido para a defesa oral.
