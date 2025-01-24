#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

// Cargar datos desde archivos
void cargarDatos(Zona zonas[]) {
    for (int i = 0; i < NUM_ZONAS; i++) {
        char nombreArchivo[50];
        sprintf(nombreArchivo, "zona_%d.txt", i + 1);
        FILE *archivo = fopen(nombreArchivo, "r");

        if (archivo == NULL) {
            printf("No se encontro el archivo %s. Se iniciara con datos vacios.\n", nombreArchivo);
            continue;
        }

        fscanf(archivo, "%s", zonas[i].nombre);
        for (int d = 0; d < DIAS_HISTORICOS; d++) {
            for (int j = 0; j < 4; j++) {
                fscanf(archivo, "%f", &zonas[i].contaminantes[d][j]);
            }
        }
        fclose(archivo);
    }
}

// Guardar datos en archivos
void guardarDatos(Zona zonas[]) {
    for (int i = 0; i < NUM_ZONAS; i++) {
        char nombreArchivo[50];
        sprintf(nombreArchivo, "zona_%d.txt", i + 1);
        FILE *archivo = fopen(nombreArchivo, "w");

        if (archivo == NULL) {
            printf("Error al guardar los datos en %s.\n", nombreArchivo);
            return;
        }

        fprintf(archivo, "%s\n", zonas[i].nombre);
        for (int d = 0; d < DIAS_HISTORICOS; d++) {
            for (int j = 0; j < 4; j++) {
                fprintf(archivo, "%.2f\n", zonas[i].contaminantes[d][j]);
            }
        }
        fclose(archivo);
    }
    printf("Datos guardados exitosamente.\n");
}

// Ingresar datos manualmente
void ingresarDatosManualmente(Zona zonas[]) {
    for (int i = 0; i < NUM_ZONAS; i++) {
        printf("\nIngrese el nombre de la zona %d: ", i + 1);
        scanf("%s", zonas[i].nombre);

        for (int d = 0; d < DIAS_HISTORICOS; d++) {
            printf("Día %d\n", d + 1);
            printf("PM2.5 (µg/m³): ");
            scanf("%f", &zonas[i].contaminantes[d][0]);

            printf("CO2 (ppm): ");
            scanf("%f", &zonas[i].contaminantes[d][1]);

            printf("SO2 (ppb): ");
            scanf("%f", &zonas[i].contaminantes[d][2]);

            printf("NO2 (ppb): ");
            scanf("%f", &zonas[i].contaminantes[d][3]);
        }
    }
    guardarDatos(zonas);
}

// Calcular promedio histórico de contaminación
void calcularPromedioHistorico(Zona zonas[]) {
    for (int i = 0; i < NUM_ZONAS; i++) {
        float sumaPM25 = 0, sumaCO2 = 0, sumaSO2 = 0, sumaNO2 = 0;

        for (int d = 0; d < DIAS_HISTORICOS; d++) {
            sumaPM25 += zonas[i].contaminantes[d][0];
            sumaCO2  += zonas[i].contaminantes[d][1];
            sumaSO2  += zonas[i].contaminantes[d][2];
            sumaNO2  += zonas[i].contaminantes[d][3];
        }

        zonas[i].promedio_PM25 = sumaPM25 / DIAS_HISTORICOS;
        zonas[i].promedio_CO2  = sumaCO2  / DIAS_HISTORICOS;
        zonas[i].promedio_SO2  = sumaSO2  / DIAS_HISTORICOS;
        zonas[i].promedio_NO2  = sumaNO2  / DIAS_HISTORICOS;
    }
}

// Evaluar calidad del aire
void evaluarCalidadAire(Zona zonas[]) {
    for (int i = 0; i < NUM_ZONAS; i++) {
        printf("\nZona: %s\n", zonas[i].nombre);
        printf("PM2.5 Promedio Ultimos 30 Días: %.2f µg/m³\n", zonas[i].promedio_PM25);

        if (zonas[i].promedio_PM25 > LIMITE_PM25) {
            printf(" Calidad del aire: MALA \n");
        } else {
            printf(" Calidad del aire: BUENA\n");
        }
    }
}

// Predicción de niveles futuros
void predecirNivelesFuturos(Zona zonas[]) {
    for (int i = 0; i < NUM_ZONAS; i++) {
        printf("\nZona: %s\n", zonas[i].nombre);
        
        for (int j = 0; j < 4; j++) {
            float tendencia = (zonas[i].contaminantes[DIAS_HISTORICOS - 1][j] - zonas[i].contaminantes[0][j]) / DIAS_HISTORICOS;
            float prediccion = zonas[i].contaminantes[DIAS_HISTORICOS - 1][j] + tendencia * 5; // Predicción a 5 días

            printf("Predicción para %s en 5 días: %.2f\n", (j == 0 ? "PM2.5" : j == 1 ? "CO2" : j == 2 ? "SO2" : "NO2"), prediccion);
        }
    }
}

// Emitir alertas
void emitirAlertas(Zona zonas[]) {
    for (int i = 0; i < NUM_ZONAS; i++) {
        if (zonas[i].promedio_PM25 > LIMITE_PM25 * 1.5) {
            printf("\n ALERTA: La zona %s tiene niveles crIticos de contaminaciOn.\n", zonas[i].nombre);
        }
    }
}

void generarReporte(Zona *zonas, int num_zonas) {
    FILE *reporte = fopen("reporte_contaminacion.dat", "w");

    if (reporte == NULL) {
        printf("Error al generar el reporte.\n");
        return;
    }

    printf("\n=== REPORTE DETALLADO DE CONTAMINACION DEL AIRE ===\n");
    fprintf(reporte, "=== REPORTE DETALLADO DE CONTAMINACION DEL AIRE ===\n");

    for (int i = 0; i < num_zonas; i++) {
        // Mostrar en pantalla y escribir en el archivo
        printf("Zona: %s\n", zonas[i].nombre);
        fprintf(reporte, "Zona: %s\n", zonas[i].nombre);

        printf("Promedios historicos:\n");
        fprintf(reporte, "Promedios historicos:\n");

        printf(" - PM2.5: %.2f µg/m³\n - CO2: %.2f ppm\n - SO2: %.2f ppb\n - NO2: %.2f ppb\n",
               zonas[i].promedio_PM25, zonas[i].promedio_CO2, zonas[i].promedio_SO2, zonas[i].promedio_NO2);

        fprintf(reporte, " - PM2.5: %.2f µg/m³\n - CO2: %.2f ppm\n - SO2: %.2f ppb\n - NO2: %.2f ppb\n",
                zonas[i].promedio_PM25, zonas[i].promedio_CO2, zonas[i].promedio_SO2, zonas[i].promedio_NO2);

        printf("Datos diarios de contaminacion:\n");
        fprintf(reporte, "Datos diarios de contaminacion:\n");

        for (int d = 0; d < DIAS_HISTORICOS; d++) {
            printf("Dia %2d -> PM2.5: %.2f | CO2: %.2f | SO2: %.2f | NO2: %.2f\n",
                   d + 1, zonas[i].contaminantes[d][0], zonas[i].contaminantes[d][1],
                   zonas[i].contaminantes[d][2], zonas[i].contaminantes[d][3]);

            fprintf(reporte, "Dia %2d -> PM2.5: %.2f | CO2: %.2f | SO2: %.2f | NO2: %.2f\n",
                    d + 1, zonas[i].contaminantes[d][0], zonas[i].contaminantes[d][1],
                    zonas[i].contaminantes[d][2], zonas[i].contaminantes[d][3]);
        }

        // Evaluacion de calidad del aire
        printf("Evaluacion de calidad del aire:\n");
        fprintf(reporte, "Evaluacion de calidad del aire:\n");

        if (zonas[i].promedio_PM25 > 100) {
            printf("  Calidad del aire: MALA (Riesgo alto)\n\n");
            fprintf(reporte, "  Calidad del aire: MALA (Riesgo alto)\n\n");
        } else {
            printf("  Calidad del aire: BUENA\n\n");
            fprintf(reporte, "  Calidad del aire: BUENA\n\n");
        }
    }

    fclose(reporte);
    printf("**Reporte generado en 'reporte_contaminacion.dat' y mostrado en pantalla.**\n");
}

