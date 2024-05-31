#include <iostream>
#include <string>
#include <memory>
#include "TestEvaluator.hpp"

using namespace std;

//Función macro para realizar una simple aserción (ASSERT) y mostrar el resultado
#define ASSERT(test_expr) te->evaluate(#test_expr, test_expr)


class Kettle
{
private:
    float maxAmountTea;
    float currentAmountTea;
public:
    Kettle(float pMaxAmount) : maxAmountTea(pMaxAmount) {} // Setear el maximo de la tetera

    ~Kettle(){}

    float getMaxAmount()
    {
        return maxAmountTea;
    }

    float getCurrentAmount()
    {
        return currentAmountTea;
    }

    float addTea_returnExcess(float teaLiters)
    {
        if(currentAmountTea + teaLiters <= maxAmountTea) 
        {
            currentAmountTea += teaLiters;
            return 0;   
        }
        else
        {
            currentAmountTea = maxAmountTea;
            return currentAmountTea + teaLiters - maxAmountTea; // Retronar sobrante
        }

    }

    bool serveTea(float teaLiters)
    {
        if (teaLiters == 0) return false; // Comprobacion de seguriudad
        
        if (currentAmountTea >= teaLiters)
        {
            currentAmountTea -= teaLiters;
            return true; // Pudo servir té
        }
        else
        {
            return false; // No hay suficiente té para servir
        }
    }    
};



void displayMenu() {
    std::cout << "Menu:\n";
    std::cout << "1. Crear una tetera\n";
    std::cout << "2. Agregar te a la tetera\n";
    std::cout << "3. Servir te de la tetera\n";
    std::cout << "4. Ver cantidad de te restante\n";
    std::cout << "5. Salir\n";
    std::cout << "Seleccione una opcion: ";
}

int main() {
    std::unique_ptr<Kettle> kettle = nullptr;
    std::unique_ptr<TestEvaluator> te = std::make_unique<TestEvaluator>();

    while (true) {
        displayMenu();
        int choice;
        std::cin >> choice;

        if (choice == 5) {
            break;
        }

        switch (choice) {
            case 1: {
                float maxAmount;
                std::cout << "Ingrese la capacidad maxima de la tetera (en litros): ";
                std::cin >> maxAmount;
                kettle = std::make_unique<Kettle>(maxAmount);
                te->title("Tetera creada");
                te->evaluate("Tetera creada con una capacidad de " + std::to_string(maxAmount) + " litros.", true);
                break;
            }
            case 2: {
                if (!kettle) {
                    std::cout << "Primero debe crear una tetera.\n";
                    break;
                }
                float teaAmount;
                std::cout << "Ingrese la cantidad de te a agregar (en litros): ";
                std::cin >> teaAmount;
                float excess = kettle->addTea_returnExcess(teaAmount);
                te->title("Agregando te");
                if (excess > 0) {
                    te->evaluate("No se pudo agregar todo el te. Excedente: " + std::to_string(excess) + " litros.", false);
                } else {
                    te->evaluate("Te agregado exitosamente.", true);
                }
                break;
            }
            case 3: {
                if (!kettle) {
                    std::cout << "Primero debe crear una tetera.\n";
                    break;
                }
                float teaAmount;
                std::cout << "Ingrese la cantidad de te a servir (en litros): ";
                std::cin >> teaAmount;
                bool served = kettle->serveTea(teaAmount);
                te->title("Sirviendo te");
                te->evaluate("El te " + std::string(served ? "fue" : "no fue") + " servido.", served);
                break;
            }
            case 4: {
                if (!kettle) {
                    std::cout << "Primero debe crear una tetera.\n";
                    break;
                }
                te->title("Cantidad de te restante");
                te->evaluate("Cantidad de te restante: " + std::to_string(kettle->getCurrentAmount()) + " litros.", true);
                break;
            }
            default: {
                std::cout << "Opcion no valida. Intente nuevamente.\n";
                break;
            }
        }
    }

    // Realizar pruebas usando la función macro
    // kettle = std::make_unique<Kettle>(2);
    // ASSERT(kettle->addTea_returnExcess(1) == 0);
    // ASSERT(kettle->addTea_returnExcess(1) == 0);
    // ASSERT(kettle->addTea_returnExcess(1) == 0); // Fallara

    // ASSERT(kettle->serveTea(1));
    // ASSERT(kettle->serveTea(1));
    // ASSERT(kettle->serveTea(1)); //Fallara

    te->summary();

    return 0;
}