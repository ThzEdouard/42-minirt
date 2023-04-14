#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#pragma pack(1) // Pour que la structure ait la taille correcte en mémoire

typedef struct {
    unsigned char signature[2];
    unsigned int fileSize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offset;
} BMPHeader;

typedef struct {
    unsigned int headerSize;
    int width;
    int height;
    unsigned short planes;
    unsigned short bitPerPixel;
    unsigned int compression;
    unsigned int imageSize;
    int xPixelsPerMeter;
    int yPixelsPerMeter;
    unsigned int colorsInColorTable;
    unsigned int importantColorCount;
} BMPInfoHeader;

typedef struct {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} BMPColor;

typedef struct {
    float x;
    float y;
    float z;
} Vector3;

typedef struct {
    Vector3 origin;
    Vector3 direction;
} Ray;

typedef struct {
    Vector3 center;
    float radius;
    BMPColor color;
} Sphere;

void normalize(Vector3 *v) {
    float length = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    v->x /= length;
    v->y /= length;
    v->z /= length;
}

int intersectSphere(Ray *ray, Sphere *sphere, float *t) {
    Vector3 oc;
    oc.x = ray->origin.x - sphere->center.x;
    oc.y = ray->origin.y - sphere->center.y;
    oc.z = ray->origin.z - sphere->center.z;
    float a = ray->direction.x * ray->direction.x + ray->direction.y * ray->direction.y + ray->direction.z * ray->direction.z;
    float b = 2.0 * (oc.x * ray->direction.x + oc.y * ray->direction.y + oc.z * ray->direction.z);
    float c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - sphere->radius * sphere->radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return 0; // No intersection
    } else {
        float sqrtDiscriminant = sqrt(discriminant);
        float root1 = (-b - sqrtDiscriminant) / (2.0 * a);
        float root2 = (-b + sqrtDiscriminant) / (2.0 * a);
        if (root1 > 0.0) {
            *t = root1;
            return 1; // Intersection at root1
        } else if (root2 > 0.0) {
            *t = root2;
            return 1; // Intersection at root2
        } else {
            return 0; // No intersection
        }
    }
}

void saveBMP(const char* filename, BMPColor* image, int width, int height) {
    BMPHeader header;
    BMPInfoHeader infoHeader;
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Failed to create BMP file\n");
        return;
    }

    // Set BMP header
    header.signature[0] = 'B';
    header.signature[1] = 'M';
    header.fileSize = sizeof(BMPHeader) + sizeof(BMPInfoHeader) + width * height * sizeof(BMPColor);
    header.reserved1 = 0;
    header.reserved2 = 0;
    header.offset = sizeof(BMPHeader) + sizeof(BMPInfoHeader);

    // Set BMP info header
    infoHeader.headerSize = sizeof(BMPInfoHeader);
    infoHeader.width = width;
    infoHeader.height = height;
    infoHeader.planes = 1;
    infoHeader.bitPerPixel = 24; // 24 bits per pixel (RGB)
    infoHeader.compression = 0;
    infoHeader.imageSize = 0;
    infoHeader.xPixelsPerMeter = 0;
    infoHeader.yPixelsPerMeter = 0;
    infoHeader.colorsInColorTable = 0;
    infoHeader.importantColorCount = 0;

    // Write BMP header and info header to file
    fwrite(&header, sizeof(BMPHeader), 1, file);
    fwrite(&infoHeader, sizeof(BMPInfoHeader), 1, file);

    // Write image data to file
    for (int y = height - 1; y >= 0; y--) {
    for (int x = 0; x < width; x++) {
    BMPColor color = image[y * width + x];
    fwrite(&color, sizeof(BMPColor), 1, file);
    }
    }

    // Close file
    fclose(file);
}

int main() {
// Camera parameters
Vector3 viewPoint = {0.0, 0.0, 0.0};
Vector3 orientation = {0.0, 0.0, -1.0};
float fov = M_PI / 2.0; // Field of view in radians
// Image resolution
int width = 800;
int height = 600;

// Sphere parameters
Sphere sphere;
sphere.center = (Vector3){0.0, 0.0, -5.0};
sphere.radius = 1.0;
sphere.color = (BMPColor){255, 0, 0}; // Red color

// Allocate memory for image buffer
BMPColor* image = (BMPColor*)malloc(width * height * sizeof(BMPColor));

// Generate rays for each pixel and check for intersection with the sphere
for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
        // Compute normalized device coordinates (NDC)
        float ndcX = (2.0 * x) / width - 1.0;
        float ndcY = (2.0 * y) / height - 1.0;

        // Compute ray direction in world coordinates
        float aspectRatio = (float)width / height;
        float tanFov = tan(fov / 2.0);
        Vector3 rayDirection;
        rayDirection.x = ndcX * aspectRatio * tanFov;
        rayDirection.y = ndcY * tanFov;
        rayDirection.z = -1.0;
        normalize(&rayDirection);

        // Create ray from camera
        Ray ray;
        ray.origin = viewPoint;
        ray.direction = rayDirection;

        // Check for intersection with the sphere
        float t;
        int intersect = intersectSphere(&ray, &sphere, &t);

        // If there is an intersection, color the pixel
        if (intersect) {
            // Set the pixel color to sphere color
            image[y * width + x] = sphere.color;
        } else {
            // Set the pixel color to background color (black)
            image[y * width + x] = (BMPColor){0, 0, 0};
}
}
}

// Save image to BMP file
saveBMP("output.bmp", image, width, height);
// Free memory
free(image);

return 0;
}
