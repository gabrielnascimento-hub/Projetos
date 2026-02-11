import os

# quando o codigo for pro server este caminho deve apontar para a pasta da rede 
pastageral = r"C:\Users\sousa\OneDrive\Documentos\setor\processos"

# Listar todos os arquivos e pastas do diretório
lista_arquivo = os.listdir(pastageral)


# Loop sobre os arquivos encontrados
for file in lista_arquivo:
    # Pegar o caminho completo do arquivo ou pasta
    arquivo_origem = os.path.join(pastageral, file)

    # Verificar se é um arquivo e não uma pasta, pois o codigo dá erro se tentar mover uma pasta
    if os.path.isfile(arquivo_origem):
        # Pegar os primeiros 7 caracteres do nome do arquivo (sem a extensão)
        # em breve deve alterar para 8 caracteres 
        nomeArquivo = file[:7]
        
        # Definir o caminho da nova pasta
        folder_path = os.path.join(pastageral, nomeArquivo)
        
        # Verificar se a pasta já existe, caso contrário, criá-la
        if not os.path.exists(folder_path):
            os.makedirs(folder_path)
            print(f'Pasta criada: {folder_path}')
        else:
            print(f'A pasta {folder_path} já existe')
        
        # Definir o caminho de destino do arquivo
        arquivo_destino = os.path.join(folder_path, file)
        
        # Mover o arquivo para a pasta correspondente
        os.rename(arquivo_origem, arquivo_destino)
        print(f'Arquivo {file} movido para {folder_path}')
    else:
        print(f'{file} é uma pasta, ignorando...')

# Exibe uma mensagem final
print('Processo de criação de pastas e movimentação de arquivos concluído.')
