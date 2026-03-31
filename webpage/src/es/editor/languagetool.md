# LanguageTool

QOwnNotes puede utilizar un servicio [LanguageTool](https://languagetool.org/) local o remoto para
realizar una **revisión gramatical y de estilo** opcional en el editor de notas.

Complementa la función de [corrección ortográfica](spellchecking.md) ya existente, en lugar de sustituirla.

## Características

- Subrayados de colores para indicar los problemas detectados de gramática, estilo, puntuación y tipografía
- Sugerencias de sustituciones en el menú contextual
- `More info...` links for rules that provide extra documentation
- `Ignore this rule` actions for rules you do not want to see again
- A quick toggle in the **Spelling** menu with `Check grammar with LanguageTool`

## Configuración

Open `Settings -> Editor` and configure the **LanguageTool** section.

- Turn on `Enable grammar and style checking with LanguageTool`
- Establezca la "URL del servidor"
  - Local servers can use something like `http://localhost:8081`
  - QOwnNotes automatically uses the `/v2/check` endpoint on that server
- Selecciona el "Idioma"
  - "Detectar automáticamente" está disponible
  - You can also enter a custom language code if needed
- Add an optional `API key` if your LanguageTool service requires one
- Adjust the `Check delay` to control how long QOwnNotes waits after typing before sending a request
- Seleccione las categorías que deben verificarse
  - `Ortografía`
  - `Gramática`
  - `Estilo`
  - `Puntuación`
  - `Tipografía`

Utilice la función "Probar conexión" para verificar que el servicio configurado sea accesible.

## Cómo funciona

- QOwnNotes comprueba los bloques del editor que están visibles, en lugar de todo el documento de una sola vez
- Las líneas en blanco, los encabezados y los bloques de código se omiten
- Requests are debounced so the service is not queried on every keystroke
- Los resultados se muestran directamente en el editor de Markdown

## Notas

- LanguageTool support is optional and depends on the feature being enabled in your build
- If the service cannot be reached, QOwnNotes shows a warning and stops checking until it is available again
- You can use it with a local self-hosted LanguageTool server or another compatible LanguageTool endpoint

## Relacionados

- [Corrector ortográfico](spellchecking.md)
- [Concepto](../getting-started/concept.md)
