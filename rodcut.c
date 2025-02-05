#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rodcut.h"

Vec read_list() {
    Vec pieces = new_vec(sizeof(PieceLengthValue));
    PieceLengthValue piece;
    while (scanf("%d, %d", &piece.length, &piece.value) == 2) {
        if (piece.length < 1 || piece.value < 1) { // Test Case #1,4 - checks valid length and values >= 1
            fprintf(stderr, "Invalid input values. Length and value must be >= 1.\n");
            vec_free(pieces);
            exit(1);
        }
        // Test Case #2 - duplicate length in list
        int duplicate = 0;
        for (int i = 0; i < vec_length(pieces); i++) {
            PieceLengthValue *existingPiece = (PieceLengthValue *)vec_items(pieces) + i;
            if (existingPiece->length == piece.length) {
                fprintf(stderr, "Duplicate length found: %d.\n", piece.length);
                duplicate = 1;
                break;
            }
        }
        if (!duplicate) {
            vec_add(pieces, &piece);
        }
    }
    if (vec_length(pieces) == 0) { // Test Case #4 - no valid input
        fprintf(stderr, "No valid input provided. Please enter at least one valid piece length and value.\n");
        vec_free(pieces);
        exit(1); 
    }
    return pieces;
}

Results calculate_max_value(Vec pieces, int rod_length) {
    Results result;
    result.rod_cuts = new_vec(sizeof(PieceLengthValue));
    result.remainder = rod_length;
    result.total_value = 0;

    while (result.remainder > 0) {
        int found = 0;
        for (int i = 0; i < vec_length(pieces); i++) {
            PieceLengthValue *piece = (PieceLengthValue *)vec_items(pieces) + i;
            if (piece->length <= result.remainder) {
                PieceLengthValue cut = {piece->length, 1};
                vec_add(result.rod_cuts, &cut);
                result.total_value += piece->value;
                result.remainder -= piece->length;
                found = 1;
                break;
            }
        }
        if (!found){
            break;
        }
    }
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <rod length>\n", argv[0]);
        return 1;
    }

    int rod_length = atoi(argv[1]);
    if (rod_length < 1) {
        fprintf(stderr, "Rod length must be greater than 0\n");
        return 1;
    }

    Vec pieces = read_list();
    Results result = calculate_max_value(pieces, rod_length);
    
    // Output
    for (int i = 0; i < vec_length(result.rod_cuts); i++) {
        PieceLengthValue *cut = (PieceLengthValue *)vec_items(result.rod_cuts) + i;
        printf("%d @ %d = %d\n", cut->value, cut->length, cut->value * cut->length);
    }
    printf("Remainder: %d\n", result.remainder);
    printf("Value: %d\n", result.total_value);

    vec_free(pieces);
    vec_free(result.rod_cuts);
    return 0;
}
