SoundEngine
-----------

Sound engine provides a wrapper around Airplay System's sound API, allowing it to interact with Airplay Studio's IwResManager resource management system.

It also uses a sound generation callback to provide ADPCM compressed sound that is decompressed on the fly.

SoundEngine.mkf cannot be built directly, it must be included in a project mkb using the subproject directive.