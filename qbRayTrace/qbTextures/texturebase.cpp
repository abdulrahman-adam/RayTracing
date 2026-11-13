
#include "texturebase.hpp"
#include <cmath>

// Construct and destruct
qbRT::Texture::TextureBase::TextureBase()
{

}

qbRT::Texture::TextureBase::~TextureBase()
{
    
}

// Function to return the color at given (U, V) location.
qbVector<double> qbRT::Texture::TextureBase::GetColor(const qbVector<double> &uvCoords)
{
    // Setup the output vector.
    qbVector<double> outputColor {4};

    // return the output.
    return outputColor;
}

// Function to set the transform matrix.
void qbRT::Texture::TextureBase::SetTransform(const qbVector<double> &translation, const double &rotation, const qbVector<double> &scale)
{
    // Build the transform matrix.
    qbMatrix2<double> rotationMatrix = {3, 3, std::vector<double> {
                                        cos(rotation), -sin(rotation), 0.0,
                                        sin(rotation), cos(rotation), 0.0,
                                        0.0, 0.0, 1.0}};

    qbMatrix2<double> scaleMatrix = {3, 3, std::vector<double> {
                                     scale.GetElement(0), 0.0, 0.0,
                                     0.0, scale.GetElement(1), 0.0,
                                     0.0, 0.0, 1.0}};

    qbMatrix2<double> translationMatrix = {3, 3, std::vector<double> {
                                     1.0, 0.0, translation.GetElement(0),
                                     0.0, 1.0, translation.GetElement(1),
                                     0.0, 0.0, 1.0}};

    // And combine to form the final transform matrix.
    m_transformMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

// Function to blend the color.
qbVector<double> qbRT::Texture::TextureBase::BlendColors(const std::vector<qbVector<double>> &inputColorList)
{
    //Setup the out color.
    qbVector<double> outputColor {3};

    // Return the output.
    return outputColor;
}

// Function to apply the transform
qbVector<double> qbRT::Texture::TextureBase::ApplyTransform(const qbVector<double> &inputVector)
{
    // Copy the input vector and modify to have there elements.
    qbVector<double> newInput {3};
    newInput.SetElement(0, inputVector.GetElement(0));
    newInput.SetElement(1, inputVector.GetElement(1));
    newInput.SetElement(2, 1.0);

    // Apply the transform.
    qbVector<double> result = m_transformMatrix * newInput;

    // Produce the output.
    qbVector<double> output {2};
    output.SetElement(0, result.GetElement(0));
    output.SetElement(1, result.GetElement(1));

    return output;
}