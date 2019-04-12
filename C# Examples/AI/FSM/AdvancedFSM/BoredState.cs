using UnityEngine;using System.Collections;public class BoredState : FSMState{    public BoredState(Transform[] wp, NPCTankController brain)     {         waypoints = wp;        stateID = FSMStateID.Bored;        curRotSpeed = 1.0f;        curSpeed = 100.0f;

        npcBrain = brain;    }    public override void Reason(Transform player, Transform npc)    {        //Check the distance with player tank        //When the distance is near, transition to chase state        if (Vector3.Distance(npc.position, player.position) <= 300.0f)        {            Debug.Log("Switch to Chase State");            npcBrain.SetTransition(Transition.SawPlayer);        }    }    public override void Act(Transform player, Transform npc)    {        Quaternion plus90 = npcBrain.turret.rotation * Quaternion.Euler(0f, 90f, 0f);        npcBrain.turret.rotation = Quaternion.Slerp(npcBrain.turret.rotation, plus90, Time.deltaTime * curRotSpeed);        npcBrain.TryEndBoredom();    }    public override void ApplyColor(Material mat)
    {
        mat.color = Color.black; // needs to be purple
    }}