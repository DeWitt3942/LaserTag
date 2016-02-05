#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

struct EntityLooking : PhysicalObject
{
    enum Direction{
        DIRECTION_STRAIGHT,
        DIRECTION_BACK,
        DIRECTION_LEFT,
        DIRECTION_RIGHT,
        DIRECTION_UP,
        DIRECTION_DOWN


    };
    triple look, head;
    Gamemode gamemode;
    double speed = 15;
    double jumpPower = 10;
    bool jumping = true;
    EntityLooking(triple pos, triple look):PhysicalObject(pos), look(look), gamemode(CREATIVE){}
    double selectedslot = 0;
    triple nextPoint;
    void setHead(triple h)
    {
        head = h;
    }
    triple getStraight(const double dt = 1)
    {
        if (gamemode==CREATIVE)
            return pos + look.mult(prima).mult(speed).mult(dt);
        else
            return pos + look.mult(prima).mult(speed).mult(dt).project(3);
    }


    triple getBack(const double dt = 1)
    {
        if (gamemode==CREATIVE)
        return pos - look.mult(prima).mult(speed).mult(dt);
        else
            return pos - look.mult(prima).mult(speed).mult(dt).project(3);

    }
    triple getLeft(const double dt = 1)
    {
        if (gamemode==CREATIVE)
        return pos - (look*head).mult(prima).mult(speed).mult(dt);
        else
            return pos - (look*head).mult(prima).mult(speed).mult(dt).project(3);

    }
    triple getRight(const double dt = 1)
    {
        if (gamemode==CREATIVE)
        return pos + (look*head).mult(prima).mult(speed).mult(dt);
        else
            return pos + (look*head).mult(prima).mult(speed).mult(dt).project(3);

    }
    triple getUp(const double dt = 1)
    {
        return pos + head.mult(prima).mult(speed).mult(dt);
    }
    triple getDown(const double dt = 1)
    {
        return pos - head.mult(prima).mult(speed).mult(dt);
    }
    void moveTo(Direction dir, const double dt = 1)
    {
        switch (dir)
        {
        case DIRECTION_STRAIGHT:
            nextPoint = getStraight();
            break;
        case DIRECTION_BACK:
            nextPoint = getBack();
            break;
        case DIRECTION_LEFT:
            nextPoint = getLeft();
            break;
        case DIRECTION_RIGHT:
            nextPoint = getRight();
            break;
        case DIRECTION_UP:
            nextPoint = getUp();
            break;
        case DIRECTION_DOWN:
            nextPoint = getDown();
            break;

        }
        if (!isNeutrino && occupied(shape, nextPoint))
            return;
        pos = nextPoint;
    }
    void handleKeys(bool* used, const double dt = 1)
    {
        if (used[0])
            moveTo(DIRECTION_STRAIGHT, dt);
            //moveStraight(dt);
        if (used[1])
            moveTo(DIRECTION_BACK, dt);
        //    moveBack(dt);
        if (used[2])
            moveTo(DIRECTION_LEFT, dt);
            //moveLeft(dt);
        if (used[3])
            moveTo(DIRECTION_RIGHT, dt);
            //moveRight(dt);
        if (used[4])
            {
                if (gamemode==CREATIVE)
                    moveTo(DIRECTION_UP, dt);
                    //                   moveUp(dt);
                else
                        jump();
            }
        if (used[5])
            moveTo(DIRECTION_DOWN,dt);
            //moveDown(dt);
        if (used[6])
            switchGameMode();
        if (used[7])
            speed+=0.05;
        if (used[8])
            speed-=0.05;
    }

    bool jump()
    {
        if (jumping)
            return false;

            jumping = true;
            velocity =Gravity::UP.mult(jumpPower);
            return true;

    }
    void handleGravity()
    {
        //move();


        switch (gamemode)
        {
            case SURVIVAL:
                if (pos.z-prima>0)
                    velocity = velocity +  Gravity::DOWN.mult(Gravity::G);

                move();
                if (pos.z-prima<=0)

                {
                    pos.z = 0;
                    velocity = triple::ZERO;
                    jumping = false;
                }
                break;
            case CREATIVE:
                break;
            default:
                break;
        }

    }
    void switchGameMode()
    {
        if (gamemode==SURVIVAL)
            gamemode=CREATIVE;
        else
            gamemode=SURVIVAL;
    }


};

#endif // CAMERA_H_INCLUDED
