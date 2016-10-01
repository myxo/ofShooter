#pragma once

#include "worldEntity.h"

#include "iostream"

// #define B2D_PLAYER_IDENTIFYER 0x01
// #define B2D_MOB_IDENTIFYER 0x02


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