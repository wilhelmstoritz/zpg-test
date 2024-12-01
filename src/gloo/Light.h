#pragma once

#include "ObserverSubject.h"
#include "Observer.h"
#include "Camera.h"

// include GLM
#include <glm/vec3.hpp> // glm::vec3

// include the standard C++ headers
#include <string>

class Model; // forward declaration due to cross-reference

class Light : public ObserverSubject<Light>, public Observer<Camera>, public Observer<Model> {
public:
	enum LightTypeE {
		DIRECTIONAL = 0,
		POINT = 1,
		SPOT = 2
	};

    struct alignas(16) lightT { // SSBO layout alignment
        alignas(4) int type; // 0 = directional light, 1 = point light, 2 = spotlight

        alignas(16) glm::vec3 position;
        alignas(16) glm::vec3 direction; // spot/directional light direction
        alignas(4) float spotCutoff; // value of cos(radians)

        // colors
        alignas(16) glm::vec3 diffuseColor;
        alignas(16) glm::vec3 specularColor;

        // attenuation coefficients
        alignas(16) glm::vec3 attenuation; // x: constant (basic light intensity), y: linear (depends on the range of the light), z: quadratic (larger value ensures faster attenuation)

        // constructor
        lightT(int t_type, const glm::vec3& t_position, const glm::vec3& t_direction, const float t_spotCutoff,
            // colors
			const glm::vec3& t_diffuseColor = glm::vec3(1.f, 1.f, 1.f),
            const glm::vec3& t_specularColor = glm::vec3(1.f, 1.f, 1.f),

            // attenuation coefficients
            const glm::vec3& t_attenuation = glm::vec3(1.f, .01f, .001f))
			: type(t_type), position(t_position), direction(t_direction), spotCutoff(t_spotCutoff),
			diffuseColor(t_diffuseColor), specularColor(t_specularColor),
            attenuation(t_attenuation) { }
    };

    Light(const std::string& t_name, const int t_type,
        const glm::vec3& t_position,
        const glm::vec3& t_direction = glm::vec3(0.f, 0.f, -1.f),
        const float t_spotCutoff = 0.f);

    std::string getName();
    int getID();
    int getNumLights();

    const lightT& getLight() const;

    /* obsolete; for backward compatibility only; use getLight() instead */
    int getType() const;
    const glm::vec3& getPosition() const;
    const glm::vec3& getDirection() const;
    float getSpotCutoff() const;

    // get colors
    const glm::vec3& getDiffuseColor() const;
    const glm::vec3& getSpecularColor() const;

    // get attenuation coefficients
    const glm::vec3& getAttenuation() const;
    /* obsolete end */

    void setID(size_t t_ID);
    void setNumLights(size_t t_numLights);

    void setLight(const lightT& t_light);

    void setPosition(const glm::vec3& t_position);
    void setDirection(const glm::vec3& t_direction);
    void setSpotCutoff(float t_spotCutoff); // value of cos(radians)
    void setSpotCutoffDegrees(float t_spotCutoffDegrees);

    // set colors
    void setDiffuseColor(const glm::vec3& t_diffuseColor);
    void setSpecularColor(const glm::vec3& t_specularColor);

    // set attenuation coefficients
    void setAttenuation(const glm::vec3& t_attenuation);

    virtual void followCamera();

    virtual void addNotifyingSubject(Camera* t_camera) override;
	virtual void addNotifyingSubject(Model* t_model) override;

protected:
    virtual void processSubject(Camera* t_camera) override;
    virtual void processSubject(Model* t_model) override;

private:
    std::string m_name;
    int m_ID;
    static int m_numLights; // number of lights; shared among all lights

    Light::lightT m_light;
};
