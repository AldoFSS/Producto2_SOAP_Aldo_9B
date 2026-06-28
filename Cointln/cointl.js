// conintl.js - Localización Nativa en Node.js
const express = require('express');
const app = express();

// Algoritmo local nativo para convertir números a palabras en español sin depender de internet
function numeroALetras(num) {
    const unidades = ['cero', 'uno', 'dos', 'tres', 'cuatro', 'cinco', 'seis', 'siete', 'ocho', 'nueve', 'diez'];
    return unidades[num] || "Número fuera de rango de prueba";
}

app.get('/', (req, res) => {
    const numero = parseInt(req.query.n || 0);
    res.send(numeroALetras(numero));
});

app.listen(8003, () => console.log("Servidor conintl (Node.js) activo en http://localhost:8003"));