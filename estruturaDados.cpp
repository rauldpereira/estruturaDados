// Função para posicionar uma embarcação
void posicionarEmbarcacao(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], char tipo, int quantidade, int jogador) {
    for (int i = 0; i < quantidade; i++) {
        bool posicaoValida = false;
        while (!posicaoValida) {
            system("cls");
            mostrarTabela(tabuleiro, "Jogador " + to_string(jogador));

            string coordenada;
            cout << "Jogador " << jogador << " - Insira as coordenadas da "
                 << (tipo == SUBMARINO ? "submarino" : tipo == CRUZADOR ? "cruzador" : tipo == PORTA_AVIOES ? "porta-aviões" : tipo == ENCOURACADO ? "encouraçado" : tipo == HIDROVIAO ? "hidrovião" : "embarcação")
                 << " " << i + 1 << " (ex: 1A): ";
            cin >> coordenada;

            // Identifica a posição da letra
            int pos = 0;
            while (pos < coordenada.length() && isdigit(coordenada[pos])) {
                pos++;
            }

            int x = stoi(coordenada.substr(0, pos)) - 1;
            char letra = coordenada[pos];
            letra = toupper(letra);
            int y = letra - 'A';

            // Verifica a direção e o sentido se for um cruzador, porta-aviões, encouraçado ou hidrovião
            char direcao, sentido;
            if (tipo == CRUZADOR || tipo == PORTA_AVIOES || tipo == ENCOURACADO || tipo == HIDROVIAO) {
                if (!determinarDirecao(direcao, sentido)) {
                    cout << "\nDireção ou sentido inválido! Tente novamente.\n";
                    cout << "Pressione Enter para continuar...";
                    cin.ignore();
                    cin.get();
                    continue;
                }
            }

            bool espacoDisponivel = false;
            int tamanho = (tipo == SUBMARINO) ? 1 : (tipo == CRUZADOR) ? 2 : (tipo == PORTA_AVIOES) ? 5 : (tipo == ENCOURACADO) ? 4 : 3;

            if (x >= 0 && x < TAMANHO_TABULEIRO && y >= 0 && y < TAMANHO_TABULEIRO) {
                if (tipo == SUBMARINO) {
                    if (tabuleiro[y][x] == ' ') {
                        tabuleiro[y][x] = SUBMARINO;
                        posicaoValida = true;
                    } else {
                        cout << "\nPosição inválida! Já existe uma embarcação nessa posição.\n";
                        cout << "Pressione Enter para continuar...";
                        cin.ignore();
                        cin.get();
                    }
                } else if (tipo == CRUZADOR || tipo == PORTA_AVIOES || tipo == ENCOURACADO) {
                    // Código existente para cruzador, porta-aviões e encouraçado
                } else if (tipo == HIDROVIAO) {
                    if (direcao == 'V') {
                        if (sentido == 'B' && x + 1 < TAMANHO_TABULEIRO && y + 2 < TAMANHO_TABULEIRO) {
                            espacoDisponivel = true;
                            for (int j = 0; j < tamanho; j++) {
                                if (tabuleiro[y + j][x + 1 - j] != ' ') {
                                    espacoDisponivel = false;
                                    break;
                                }
                            }
                            if (espacoDisponivel) {
                                for (int j = 0; j < tamanho; j++) {
                                    tabuleiro[y + j][x + 1 - j] = tipo;
                                }
                                posicaoValida = true;
                            }
                        } else if (sentido == 'C' && x - 1 >= 0 && y - 2 >= 0) {
                            espacoDisponivel = true;
                            for (int j = 0; j < tamanho; j++) {
                                if (tabuleiro[y - j][x - 1 + j] != ' ') {
                                    espacoDisponivel = false;
                                    break;
                                }
                            }
                            if (espacoDisponivel) {
                                for (int j = 0; j < tamanho; j++) {
                                    tabuleiro[y - j][x - 1 + j] = tipo;
                                }
                                posicaoValida = true;
                            }
                        }
                    } else if (direcao == 'H') {
                        if (sentido == 'D' && x + 2 < TAMANHO_TABULEIRO && y + 1 < TAMANHO_TABULEIRO) {
                            espacoDisponivel = true;
                            for (int j = 0; j < tamanho; j++) {
                                if (tabuleiro[y + 1 - j][x + j] != ' ') {
                                    espacoDisponivel = false;
                                    break;
                                }
                            }
                            if (espacoDisponivel) {
                                for (int j = 0; j < tamanho; j++) {
                                    tabuleiro[y + 1 - j][x + j] = tipo;
                                }
                                posicaoValida = true;
                            }
                        } else if (sentido == 'E' && x - 2 >= 0 && y - 1 >= 0) {
                            espacoDisponivel = true;
                            for (int j = 0; j < tamanho; j++) {
                                if (tabuleiro[y - 1 + j][x - j] != ' ') {
                                    espacoDisponivel = false;
                                    break;
                                }
                            }
                            if (espacoDisponivel) {
                                for (int j = 0; j < tamanho; j++) {
                                    tabuleiro[y - 1 + j][x - j] = tipo;
                                }
                                posicaoValida = true;
                            }
                        }
                    } else {
                        cout << "\nSentido inválido! Tente novamente.\n";
                        cout << "Pressione Enter para continuar...";
                        cin.ignore();
                        cin.get();
                    }
                }
            } else {
                cout << "\nCoordenada fora do intervalo! Insira novamente.\n";
                cout << "Pressione Enter para continuar...";
                cin.ignore();
                cin.get();
            }

            if (!posicaoValida) {
                cout << "\nPosição inválida para a embarcação! Tente novamente.\n";
                cout << "Pressione Enter para continuar...";
                cin.ignore();
                cin.get();
            }
        }
    }
}
