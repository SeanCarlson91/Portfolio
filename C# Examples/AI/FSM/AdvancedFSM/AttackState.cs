using UnityEngine;
using System.Collections;

public class AttackState : FSMState
{
    public AttackState(Transform[] wp, NPCTankController brain) 
    { 
        waypoints = wp;
        stateID = FSMStateID.Attacking;
        curRotSpeed = 1.0f;
        curSpeed = 100.0f;

        npcBrain = brain;

        //find next Waypoint position
        FindNextPoint();
    }

    public override void Reason(Transform player, Transform npc)
    {
        //Check the distance with the player tank and if not in range, chase the player
        destPos = player.position;
        float dist = Vector3.Distance(npc.position, player.position);
        
        // Handle health transition

        if (dist >= 200.0f && dist < 300.0f)
        {
            Debug.Log("Switch to Chase State");
            npcBrain.SetTransition(Transition.SawPlayer);
        }
        else if (dist >= 300.0f)
        {
            Debug.Log("Switching to Patrol");
            npcBrain.SetTransition(Transition.LostPlayer);
        }  
    }

    public override void Act(Transform player, Transform npc)
    {
        //Set the target position to the player position
        destPos = player.position;

        //Always Turn the turret towards the player
        Quaternion turretRotation = Quaternion.LookRotation(destPos - npc.position);
        Transform turret = npc.GetComponent<NPCTankController>().turret;
        turret.rotation = Quaternion.Slerp(turret.rotation, turretRotation, Time.deltaTime * curRotSpeed);

        //Shoot bullet
        npc.GetComponent<NPCTankController>().ShootBullet();
    }

    public override void ApplyColor(Material mat)
    {
        mat.color = Color.red;
    }
}