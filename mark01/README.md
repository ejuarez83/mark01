# mark01

Mini dron DIY con ESP32-C3, motores coreless, sensores y control v¡a interfaz web moderna inspirada en control de PlayStation.

---

## ?? Idea del Proyecto (conversaci¢n original con Jarvis)

Este es un proyecto **personal y confidencial** basado en la construcci¢n de un mini dron tipo cuatrimotor. El objetivo es desarrollar un sistema completo de control y monitoreo usando componentes DIY, conectividad WiFi y una interfaz web visual.

---

### ?? Componentes confirmados
1. **Microcontrolador**: ESP32-C3 Mini Super Plus (USB-C)
2. **Motores**: Coreless 3.7V 46000RPM 7x25MM (x4)
3. **Control de potencia**: MOSFET IRFZ44N (1 por motor)
4. **Sensores**:
   - HC-SR04 frontal  detecci¢n de obst culos
   - HC-SR04 inferior  detecci¢n de altura para aterrizaje
   - Sensor de voltaje  monitoreo de bater¡a
   - MPU6050  giroscopio e inclinaci¢n
5. **Cuerpo del dron**: Impreso en 3D con PLA

---

### ?? Interfaz Web (v¡a WiFi)
6. El ESP32-C3 servir  una **interfaz web embebida**, accesible v¡a navegador desde PC o celular.
7. Estilo inspirado en **control de PlayStation**.
8. Controles esperados:
   - Joystick virtual para direcci¢n
   - Botones para encender/apagar motores
   - Despegue / aterrizaje manual
   - Alerta visual por bater¡a baja
   - Indicadores: altitud, voltaje, direcci¢n

---

### ?? L¢gica del sistema (resumen)
9. **Modo manual** con control desde la web.
10. **Modo autom tico** para secuencias de despegue y aterrizaje.
11. **Seguridad**:
    - Aterrizaje forzado por bater¡a baja
    - Aterrizaje si se pierde conexi¢n WiFi por m s de 1 minuto

---

### ? Tecnolog¡a usada
- Programaci¢n con **Arduino IDE**
- Comunicaci¢n WiFi (no Bluetooth)
- Interfaz embebida (HTML servida desde c¢digo)
- Organizaci¢n de c¢digo en m¢dulos (motores, sensores, red)
- GitHub como control de versiones y documentaci¢n

---

## ?? Estructura del proyecto

```
mark01/
ÃÄÄ src/
³   ÃÄÄ mark01.ino
³   ÃÄÄ motores.h/.cpp
³   ÃÄÄ sensores.h/.cpp
³   ÃÄÄ wifi_ui.h/.cpp
³   ÀÄÄ web_ui.h
ÃÄÄ docs/
³   ÀÄÄ dron_flujo.puml
ÃÄÄ README.md
ÀÄÄ .gitignore
```

---

## ?? Estado actual
? Idea validada y documentada
? Estructura del proyecto creada
?? Siguiente paso: implementar l¢gica WiFi + UI web embebida
?? Luego: integrar sensores y motores uno por uno

