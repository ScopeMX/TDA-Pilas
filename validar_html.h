#ifndef __VALIDAR_HTML_H__
#define  __VALIDAR_HTML_H__

struct etiquetas {
	char		etiqueta  [20];
	int		unico;
};

typedef struct etiquetas Etiqueta;

int		almacenar_documento_html(FILE *);

int		encontrar_apertura(char);

int		encontrar_etiqueta(char *, int);

int		encontrar_cierre(char);

void		es_unica   ();

void		evaluar_comentario();

void		evaluar_comillas();

void		validar_documento_html();

void		cerrar_etiqueta();

void		guardar    ();

void		evaluar_etiqueta();

void reiniciar_variables();

void validar_cierre_etiqueta();

#endif
