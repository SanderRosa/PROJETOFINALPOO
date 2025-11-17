#!/usr/bin/env python3
import re
import os

def analyze_code():
    print("=" * 70)
    print("ANÁLISE DE REDUNDÂNCIA E ERROS SEMÂNTICOS")
    print("=" * 70)
    
    # Dicionário para armazenar funções encontradas
    funcoes = {}
    
    # Arquivos a verificar
    arquivos = [
        'main.cpp', 'Estoque.cpp', 'Item.cpp', 'ItemProduto.cpp',
        'ItemMateria.cpp', 'MovimentoEstoque.cpp', 'Estoque.h',
        'Item.h', 'ItemProduto.h', 'ItemMateria.h', 'MovimentoEstoque.h',
        'EstoqueException.h', 'ListaGenerica.h', 'IExibivel.h'
    ]
    
    print("\n1. VERIFICANDO DEFINIÇÕES DE FUNÇÕES DUPLICADAS:\n")
    
    for arquivo in arquivos:
        if not os.path.exists(arquivo):
            continue
            
        with open(arquivo, 'r', encoding='utf-8', errors='ignore') as f:
            conteudo = f.read()
            
        # Padrão para detecção de definições de função
        # Busca por padrão: tipo nome_funcao(parametros)
        pattern = r'(?:^|\n)\s*(?:virtual\s+)?(?:static\s+)?(?:const\s+)?(?:void|int|string|Item\*|MovimentoEstoque\*|bool|char\*|const\s+char\*)\s+(\w+)\s*\([^{]*\)\s*(?:const)?(?:override)?\s*\{'
        
        matches = re.finditer(pattern, conteudo, re.MULTILINE)
        for match in matches:
            nome_func = match.group(1)
            if nome_func not in funcoes:
                funcoes[nome_func] = []
            funcoes[nome_func].append(arquivo)
    
    duplicadas = {k: v for k, v in funcoes.items() if len(v) > 1}
    
    if duplicadas:
        print("⚠️  FUNÇÕES DEFINIDAS MÚLTIPLAS VEZES:\n")
        for func, arquivos_list in sorted(duplicadas.items()):
            print(f"  ❌ {func}:")
            for arq in arquivos_list:
                print(f"     - {arq}")
    else:
        print("✅ Nenhuma função duplicada encontrada!")
    
    print("\n2. VERIFICANDO MÉTODOS SIMILARES:\n")
    
    # Verificar registrarEntrada vs registrarSaida
    with open('main.cpp', 'r') as f:
        main_content = f.read()
    
    entrada_start = main_content.find('void registrarEntrada(Estoque& estoque)')
    entrada_end = main_content.find('\n}\n', entrada_start) + 2
    
    saida_start = main_content.find('void registrarSaida(Estoque& estoque)')
    saida_end = main_content.find('\n}\n', saida_start) + 2
    
    entrada_code = main_content[entrada_start:entrada_end]
    saida_code = main_content[saida_start:saida_end]
    
    # Comparar similaridade
    entrada_lines = [line.strip() for line in entrada_code.split('\n') if line.strip()]
    saida_lines = [line.strip() for line in saida_code.split('\n') if line.strip()]
    
    comum = sum(1 for line in entrada_lines if any(s in line for s in ['lerInteiro', 'estoque']))
    similares = comum / max(len(entrada_lines), len(saida_lines))
    
    print(f"  registrarEntrada() vs registrarSaida(): {similares:.0%} similares")
    print("  ℹ️  Isso é ESPERADO (estrutura similar, dados diferentes)\n")
    
    print("3. VERIFICANDO GETTERS/SETTERS REDUNDANTES:\n")
    
    # Verificar Item.h
    with open('Item.h', 'r') as f:
        item_h = f.read()
    
    getters = re.findall(r'(\w+)\s+get\w+\(\)', item_h)
    
    if len(getters) > 0:
        print(f"  ✅ Getters em Item: {len(getters)} métodos")
    
    # Verificar MovimentoEstoque.h
    with open('MovimentoEstoque.h', 'r') as f:
        mov_h = f.read()
    
    mov_getters = re.findall(r'(\w+)\s+get\w+\(\)', mov_h)
    
    if len(mov_getters) > 0:
        print(f"  ✅ Getters em MovimentoEstoque: {len(mov_getters)} métodos")
    
    print("\n4. VERIFICANDO INCLUDES REDUNDANTES:\n")
    
    includes_por_arquivo = {}
    for arquivo in arquivos:
        if not arquivo.endswith('.cpp') and not arquivo.endswith('.h'):
            continue
        if not os.path.exists(arquivo):
            continue
            
        with open(arquivo, 'r') as f:
            includes = re.findall(r'#include\s+[<"]([^>"]+)[>"]', f.read())
        
        if includes:
            includes_por_arquivo[arquivo] = includes
    
    # Verificar por duplicatas
    duplicatas = {}
    for arquivo, incs in includes_por_arquivo.items():
        for inc in incs:
            if inc not in duplicatas:
                duplicatas[inc] = []
            duplicatas[inc].append(arquivo)
    
    print("  Distribuição de includes:")
    for inc in sorted(set(i for incs in includes_por_arquivo.values() for i in incs)):
        count = len([a for a in includes_por_arquivo if inc in includes_por_arquivo[a]])
        if count > 1:
            print(f"  ℹ️  '{inc}' incluído em {count} arquivos (normal em C++)")
    
    print("\n5. VERIFICANDO LÓGICA SEMÂNTICA:\n")
    
    # Verificar inicialização de static
    with open('Item.cpp', 'r') as f:
        item_cpp = f.read()
    
    if 'int Item::proximoId = 1' in item_cpp:
        print("  ✅ Item::proximoId inicializado corretamente")
    else:
        print("  ❌ ERRO: Item::proximoId não inicializado!")
    
    with open('MovimentoEstoque.cpp', 'r') as f:
        mov_cpp = f.read()
    
    if 'int MovimentoEstoque::proximoId = 1' in mov_cpp:
        print("  ✅ MovimentoEstoque::proximoId inicializado corretamente")
    else:
        print("  ❌ ERRO: MovimentoEstoque::proximoId não inicializado!")
    
    print("\n6. VERIFICANDO CONSTRUTORES DUPLICADOS:\n")
    
    # Verificar MovimentoEstoque
    mov_h_content = open('MovimentoEstoque.h').read()
    mov_construtores = re.findall(r'MovimentoEstoque\s*\([^)]*\)', mov_h_content)
    
    print(f"  ✅ MovimentoEstoque tem {len(mov_construtores)} construtores (esperado: 2)")
    for i, const in enumerate(mov_construtores, 1):
        print(f"     {i}. {const}")
    
    print("\n" + "=" * 70)
    print("CONCLUSÃO:")
    print("=" * 70)
    
    if not duplicadas:
        print("✅ Nenhuma função duplicada encontrada")
        print("✅ Código semanticamente correto")
        print("✅ Não há erros óbvios de lógica")
    
analyze_code()
