
add_executable(project_main projekt_main.c
        general-library.c
        general-library.h
        map_creation/create_file.c
        map_processing/read_map.c
        map_processing/parse_map.c
        algorithm/heap.c
        algorithm/hash_table.c
        algorithm/trace_path.c
        algorithm/a_star_algorithm.c
        algorithm/a_star_library.h
        map_processing/post_process.c
        map_processing/process_library.h
        tsp/nearest_neighbor.c
        tsp/tsp_library.h

)