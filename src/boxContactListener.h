#pragma once

#include "worldEntity.h"

// #include "iostream"


// class for Box2d collision handling
class ContactListener : public b2ContactListener {
    void BeginContact(b2Contact* contact) {
        
        worldEntity* entityA = static_cast<worldEntity*>
                (contact->GetFixtureA()->GetBody()->GetUserData());
                
        worldEntity* entityB = static_cast<worldEntity*>
                (contact->GetFixtureB()->GetBody()->GetUserData());

        entityA->collision_event(entityB);
        entityB->collision_event(entityA);
    }
};