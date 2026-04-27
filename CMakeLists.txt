cmake_minimum_required(VERSION 3.10)
project(Kl0ck LANGUAGES C)

# 1. Chercher raylib sur le système
find_package(raylib REQUIRED)

# 2. Créer l'exécutable
add_executable(Kl0ck src/kl0ck.c)

# 3. Lier avec la bibliothèque trouvée
target_link_libraries(Kl0ck raylib)

# Optionnel : Standard C
set_target_properties(Kl0ck PROPERTIES C_STANDARD 99)
