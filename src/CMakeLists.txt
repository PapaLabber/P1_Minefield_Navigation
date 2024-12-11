
add_executable(project_main projekt_main.c
        function-library.c
        function-library.h
        map_creation/map_initializer.c
        map_creation/map_input.c
        map_creation/map_create_objects.c
        map_creation/map_object_check.c
        map_creation/create_file.c
        map_processing/read_map.c
        map_processing/parse_map.c
        map_processing/process_map.c
        algorithm/heap.c
        algorithm/hash_table.c
        algorithm/trace_path.c
        algorithm/a_star_algorithm.c
        algorithm/a_star_library.h


)
