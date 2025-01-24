#ifndef FUNCIONES_H
#define FUNCIONES_H

#define NUM_ZONAS 5
#define DIAS_HISTORICOS 30
#define LIMITE_PM25 25.0

// Estructura para almacenar datos de una zona
typedef struct {
    char nombre[50];
    float contaminantes[DIAS_HISTORICOS][4]; // Matriz de contaminantes
    float promedio_PM25;
    float promedio_CO2;
    float promedio_SO2;
    float promedio_NO2;
} Zona;


// Prototipos de funciones
void cargarDatos(Zona zonas[]);
void guardarDatos(Zona zonas[]);
void ingresarDatosManualmente(Zona zonas[]);
void calcularPromedioHistorico(Zona zonas[]);
void evaluarCalidadAire(Zona zonas[]);
void predecirNivelesFuturos(Zona zonas[]);
void emitirAlertas(Zona zonas[]);
void generarRecomendaciones(Zona zonas[]);
void generarReporte(Zona zonas[]);

#endif
