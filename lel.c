#include <stdio.h>
#include <string.h>

int main ()
{
    FILE * archivo_etiquetas = NULL;
    char buffer[20];

    archivo_etiquetas = fopen("etiquetas_html.rtf", "r");
    if(archivo_etiquetas == NULL){
        printf("%s\n", "Error al abrir el archivo de las etiquetas html.");
        return 0;
    }

    while(feof(archivo_etiquetas) == 0){
        fscanf(archivo_etiquetas, "%s", buffer);
        printf("%s\n", buffer);
    }
    return 0;
}
