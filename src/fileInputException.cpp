#include "../include/fileInputException.hpp"

const char *fileInputException::what() const throw()
{
    return "Falha ao abrir ou encontrar arquivos de entrada";
}