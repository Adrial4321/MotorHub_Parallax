# Botler - Robot de Catering
## Guía y documentación

Este proyecto presenta el diseño para el manejo de un robot diferencial con la capacidad de operar en un entorno cerrado en relación en la industria del servicio (catering), el robot es capaz de:

- Mapear: mediante el sensor RPlidar A1, se utilizó el algoritmo de localización y mapeo simultáneo (SLAM) hector mapping para así generar un mapa 2D del entorno de trabajo.

- Navegar: mediante el algoritmo AMCL y DWAPlanner se logró la planeación y navegación de nuestro robot en el entorno previamente mapeado.

La arquitectura del robot se basa en la comunicación entre 2 micro controladores, el microcontrolador P2 Edge es el encargado del funcionamiento de los motores Hub mediante la recepción de valores de velocidad enviados por el ESP32, el microcoontrolador ESP32 permite la interación con ROS para la realización de mapeo por TeleOp o navegación en el entorno cerrado.

Referencia del diagrama de conexiones para el funcionamiento del robot.

![image](https://github.com/user-attachments/assets/10fb5bba-ee98-44d1-9b0a-e2b8ebb918dd)

### Librería para el control de motores HUB
El funcionamiento y control de los motores HUB fue gracias a la librería [ironsheep](https://github.com/ironsheep), se adjunta el link del repisotorio con toda la información con respecto a la librería: [P2-BLDC-Motor-Control](https://github.com/ironsheep/P2-BLDC-Motor-Control).

> Se recomienda descargar la carpeta /src y colocar el código "Control_MotoresHun" en la misma carpeta

El archivo isp_bldc_motor_userconfig.spin2 es el encargado de la configuración de los drivers para el motor, de acuerdo a las características del motor, pines utilizados y tipo de bateria. Se utilizó esta configuración para el control de ambos motores.
    
    MOTOR_TYPE = MOTR_6_5_INCH

    LEFT_MOTOR_BASE = PINS_P0_P15
    RIGHT_MOTOR_BASE = PINS_P16_P31

    DRIVE_VOLTAGE = PWR_25p9V

    WHEEL_DIA_IN_INCH = 6.5   ' 6.5 inches (floating point constant)

    LEFT_BOARD_TYPE = BRD_AUTO_DET
    RIGHT_BOARD_TYPE = BRD_AUTO_DET
La configuración se realiza en esta sección
![image](https://github.com/user-attachments/assets/1b1d9324-8801-496c-af04-74388578f606)

Con las configuraciones respectivas se trabaja en el código main para la recepción de datos y control de los motores hub.

### Control de motores HUB a través de comunicación serial
Para el código de control de motores HUB se utilizaron 3 librerías, las cuales son:

![image](https://github.com/user-attachments/assets/ade7b136-b224-4690-bc44-cbf953cc8a64)

La librería para realizar la comunicación serial entre los 2 microcontroladores es "jm_fullduplexserial", para activar esta comunicación se activa la siguiente función.

             serial.start(60, 61, 0, BAUD_RATE)
> 60 y 61 son los pines Rx y Tx, el Baud Rate se lo configuró en 57600 para evitar interferencias en la comunicación, se recomienda no cambiar estos valores

Hay que tomar en cuenta que la comunicación serial del P2 Edge funciona mediante la lectura de caracter por caracter, es decir, si se envía un string con 4 letras, el P2 Edge va a leer letra por letra, por lo tanto hay que realizar una función que concatene dichos caracteres, para esto se realizó la creación de las siguientes variables:

          rx_buffer := serial.rxcheck()
          rx2_buffer := serial.rxcheck()
          rx3_buffer := serial.rxcheck()
          rx4_buffer := serial.rxcheck()
          rx5_buffer := serial.rxcheck()
          rx6_buffer := serial.rxcheck()

> El formato del String enviado por el ESP32 es ±XX±XX, por lo tanto, se requiere un total de 6 variables por los 6 caracteres que siempre va a recibir.

Para la verificación si los caracteres recibidos son válidos se utiliza el siguiente condicional:
       
       if rx_buffer <> "+" and rx_buffer <> "-"
         serial.rxflush()

- rx_buffer <> "+" and rx_buffer <> "-"
Verifica que el contenido de rx_buffer no sea ni "+" ni "-". En Spin2, <> significa "diferente de".
- serial.rxflush()
Si rx_buffer no es ni "+" ni "-", se limpia el buffer de recepción serie con rxflush(), descartando los datos no deseados.

Se verifica si el primer y cuarto caracter es positivo o negativo para posterior comprobar las siguientes condiciones:

        if rx_buffer == "-"
            if rx2_buffer <> -1
              if rx3_buffer <> -1
                vel_izq := -(rx2_buffer-48)*10 -(rx3_buffer-48)
              else
                vel_izq := -(rx2_buffer-48)

- Se verifica que rx2 y rx3 no sea -1, para comprobar que existan caracteres válidos.
- En el caso de tener 2 dígitos se realiza la siguiente operación:
    - rx2_buffer - 48 y rx3_buffer - 48:
    - En ASCII, los números "0" a "9" tienen valores entre 48 y 57.
    - Restar 48 convierte el carácter en su valor numérico.
    - rx2_buffer-48 representa la decena y rx3_buffer-48 la unidad.
    - Se multiplica la decena por 10 y se suma la unidad.
    - Como rx_buffer era "-", se usa -() para que el número sea negativo.
- En el caso que solo exista un dígito se utiliza:

      vel_izq := -(rx2_buffer-48) 

- Se convierte ese único carácter en número y se asigna con signo negativo.

> Estas operaciones se realizan tanto para el motor izquierdo y el derecho.

Finalmente, al tener los valores de vel_izq y vel_der se utiliza la librería de motores Hub para setear la potencia de los motores con la siguiente función:

                  wheels.driveAtPower(vel_izq,vel_der)

Hay que tomar en cuenta que se setear el porcentaje de velocidad para cada motor, para setear la velocidad máxima del motor se utilizó al comienzo la siguiente función:

        wheels.setMaxSpeed(14) 

> Estos valores se pueden configurar de acuerdo a las necesidades del usuario.





    
