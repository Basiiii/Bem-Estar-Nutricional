# Biblioteca GestorDadosIO

A Biblioteca `GestorDadosIO` é responsável por fornecer funcionalidades de importação e exportação de dados a partir de ficheiros. Esta biblioteca é parte integrante do projeto Bem Estar, que tem como objetivo apoiar o bem-estar e cuidados nutricionais.

## Funcionalidades

### Importar Dados

A biblioteca suporta a importação de diferentes tipos de dados, incluindo pacientes, dietas e planos nutricionais. Para importar dados, utilize as seguintes funções:

- `ImportarDadosFichBinario`: Importa dados de um ficheiro binário.
- `ImportarPacientesFichTexto`: Importa dados de pacientes de um ficheiro de texto.
- `ImportarDietasFichTexto`: Importa dados de dietas de um ficheiro de texto.
- `ImportarPlanosFichTexto`: Importa dados de planos de um ficheiro de texto.

### Exportar Dados

Além da importação, a biblioteca permite exportar dados para ficheiros. A função correspondente é:

- `ExportarDadosFichBinario`: Exporta dados para um ficheiro binário.
