const express = require('express');
const app = express();
const port = 3000;

app.set('trust proxy', true);

app.get('/', (req, res) => {
  const ip = req.ip;
  const matchedIp = ip.match(/\d+\.\d+\.\d+\.\d+/);
  const ipAddr = matchedIp ? matchedIp[0] : ip;

  res.send(`
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Exercicio de Redes</title>
        <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css" rel="stylesheet">
        <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js"></script>
        <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.bundle.min.js"></script>
        <script>

          function updateTime() {
            const date = new Date();
            const formattedDateTime = \`\${date.getFullYear()}-\${(date.getMonth() + 1)
              .toString()
              .padStart(2, '0')}-\${date
              .getDate()
              .toString()
              .padStart(2, '0')} \${date.getHours().toString().padStart(2, '0')}:\${date
              .getMinutes()
              .toString()
              .padStart(2, '0')}:\${date.getSeconds().toString().padStart(2, '0')}\`;
            document.getElementById('datetime').innerText = formattedDateTime;
          }

          setInterval(updateTime, 1000);
        </script>
    </head>
    <body>
        <div class="container mt-5">
            <h1>Suas informações:</h1>
            <p>Endereço IP: ${ipAddr}</p>
            <p>Data e Hora: <span id="datetime"></span></p>
        </div>
    </body>
    </html>
  `);
});

app.listen(port, () => {
  console.log(`Servidor Express rodando em http://localhost:${port}`);
});
