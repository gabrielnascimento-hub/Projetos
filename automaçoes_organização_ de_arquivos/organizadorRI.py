import os

# Defina o diretório onde estão os arquivos
pastageral = r"C:\Users\sousa\OneDrive\Documentos\setor\processos"

# Listar todos os arquivos e pastas do diretório
lista_arquivo = os.listdir(pastageral)

# Loop sobre os arquivos encontrados
for file in lista_arquivo:
    # Defina o caminho completo do arquivo ou pasta
    caminho_completo = os.path.join(pastageral, file)
    
    # Verificar se é um arquivo (não uma pasta)
    if os.path.isfile(caminho_completo):
        # Pegar os primeiros 7 caracteres do nome do arquivo (sem a extensão)
        #RI-12345
        nomeArquivo = file[:5]
        
        # Definir o caminho da nova pasta
        folder_path = os.path.join(pastageral, nomeArquivo)
        
        # Verificar se a pasta j� existe, caso contrário, criá-la
        if not os.path.exists(folder_path):
            os.makedirs(folder_path)    
            print(f'Pasta criada: {folder_path}')
        else:
            print(f'A pasta {folder_path} já existe')

        # Definir os caminhos de origem e destino do arquivo
        arquivo_origem = os.path.join(pastageral, file)
        arquivo_destino = os.path.join(folder_path, file)

        # Mover o arquivo para a pasta correspondente
        os.rename(arquivo_origem, arquivo_destino)
        print(f'Arquivo {file} movido para {folder_path}')
    else:
        print(f'{file}  uma pasta, ignorado.')

# Exibe uma mensagem final
print('Processo de criação de pastas e movimentação de arquivos concluído.')
