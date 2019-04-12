using UnityEngine;using System.Collections;public class HealState : FSMState{    public HealState(Transform[] wp, NPCTankController brain)     {         waypoints = wp;        stateID = FSMStateID.Healing;        curRotSpeed = 1.0f;        curSpeed = 100.0f;        npcBrain = brain;    }    public override void Reason(Transform player, Transform npc)    {        if (npcBrain.IsHealing == false && Mathf.Approximately(npcBrain.Health, 100f))
        {
            if (Vector3.Distance(npc.position, player.position) <= 300f)
                npcBrain.SetTransition(Transition.SawPlayer);
            else
                npcBrain.SetTransition(Transition.LostPlayer);
        }    }    public override void Act(Transform player, Transform npc)    {        if (npcBrain.IsHealing)
        {
            npcBrain.Heal();
        }

        destPos = npcBrain.HealingTransform.position;

        if (Vector3.Distance(destPos, npc.position) >= 50f)
        {  
            Quaternion targetRotation = Quaternion.LookRotation(destPos - npc.position);
            npc.rotation = Quaternion.Slerp(npc.rotation, targetRotation, Time.deltaTime * curRotSpeed);

            npc.Translate(Vector3.forward * Time.deltaTime * curSpeed);
        }    }    public override void ApplyColor(Material mat)
    {
        mat.color = Color.white;
    }}