/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesferr <alesferr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 16:50:32 by alesferr          #+#    #+#             */
/*   Updated: 2026/07/03 18:03:14 by alesferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main(void)
{
    FILE    *arquivo;
    char    linha[100];
    //"r" de read(ler) o arquivo
    arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return (1);
    }
    else
        printf("Arquivo aberto com sucesso!\n");
    //fgets lê uma linha inteira de texto
    //sizeof serve para descobrir quantos bytes um tipo de dado ou uma variável ocupa na memória
    while (fgets(linha, sizeof(linha), arquivo) != NULL)
        printf("%s", linha);
}