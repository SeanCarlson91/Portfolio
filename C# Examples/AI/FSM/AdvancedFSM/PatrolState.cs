using UnityEngine;using System.Collections;public class PatrolState : FSMState{    public PatrolState(Transform[] wp, NPCTankController brain)     {         waypoints = wp;        stateID = FSMStateID.Patrolling;        curRotSpeed = 1.0f;        curSpeed = 100.0f;

        npcBrain = brain;    }    public override void Reason(Transform player, Transform npc)    {
        //Check the distance with player tank
        //When the distance is near, transition to chase state
        if (Vector3.Distance(npc.position, player.position) <= 300.0f)        {            Debug.Log("Switch to Chase State");            npcBrain.SetTransition(Transition.SawPlayer);        }        else            npcBrain.TryStartBoredom();    }    public override void Act(Transform player, Transform npc)    {        //Find another random patrol point if the current point is reached		        if (Vector3.Distance(npc.position, destPos) <= 100.0f)        {            Debug.Log("Reached to the destination point\ncalculating the next point");            FindNextPoint();        }        //Rotate to the target point        Quaternion targetRotation = Quaternion.LookRotation(destPos - npc.position);        npc.rotation = Quaternion.Slerp(npc.rotation, targetRotation, Time.deltaTime * curRotSpeed);        //Go Forward        npc.Translate(Vector3.forward * Time.deltaTime * curSpeed);    }    public override void ApplyColor(Material mat)
    {
        mat.color = Color.green;
    }}