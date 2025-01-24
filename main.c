#include <stdio.h>
#include "funciones.h"

int main() {
    Zona zonas[NUM_ZONAS];  // Arreglo de estructuras para almacenar los datos de las zonas
    int opcion;

    // Cargar datos al iniciar el programa
    cargarDatos(zonas);

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Ingresar datos manualmente\n");
        printf("2. Evaluar calidad del aire\n");
        printf("3. Calcular promedio historico (30 dias)\n");
        printf("4. Predecir niveles futuros\n");
        printf("5. Emitir alertas\n");
        printf("6. Generar recomendaciones\n");
        printf("7. Generar reporte\n");
        printf("8. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                ingresarDatosManualmente(zonas);
                break;
            case 2:
                evaluarCalidadAire(zonas);
                break;
            case 3:
                calcularPromedioHistorico(zonas);
                break;
            case 4:
                predecirNivelesFuturos(zonas);
                break;
            case 5:
                emitirAlertas(zonas);
                break;
            case 6:
                generarRecomendaciones(zonas);
                break;
            case 7:
                generarReporte(zonas);
                break;
            case 8:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 8);

    return 0;
}
