using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class AIStopAttacking : MonoBehaviour {

    // Use this for initialization
    private void OnTriggerExit(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            GetComponentInParent<Patrol>().attacking = false;
            Debug.Log("Exit");
            GetComponentInParent<Patrol>().GotoNextPoint();
            GetComponentInParent<NavMeshAgent>().autoBraking = false;
            GetComponentInParent<NavMeshAgent>().stoppingDistance = 0;
        }
    }
}
